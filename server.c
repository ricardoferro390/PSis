#include "ProtoBuffers.pb-c.h"
#include "message.h"
#include "login_list.h"
#include "log.h"

#define TICK_TIME 5
#define TOLERANCE 3
#define RELAUNCHER "relauncher"
#define FIFO_NAME "/tmp/AH_AH_AH_AH_STAYIN_ALIVE"
#define INFINITY 99999999

int client_exit_flag, accepter_exit_flag, stop_broadcast;
int broadcast_fifo_write;
int admin_sock, accepter_sock;
int admin_conected;
pthread_mutex_t broadcast_mutex;
pthread_t thread_imAlive, thread_keepRelauncherAlive, thread_isAlive;

int openFIFO_server(int mode){
	int fd_fifo=-1;
	
	if (mode==0){
		fd_fifo = open(FIFO_NAME, O_RDONLY|O_NONBLOCK);
	}else if(mode==1){
		fd_fifo = open(FIFO_NAME, O_WRONLY);
	}
	
	sync();
	printf("Opened FIFO (Relauncher)\n");
	
	return fd_fifo;
}

int thread_sock_ini(int port){
	int exit_flag=0;
	struct sockaddr_in server_addr, client_addr;
	int new_sock, sock_fd_accepter;
	
	// criação do socket
	sock_fd_accepter = socket(AF_INET, SOCK_STREAM, 0);
	perror("socket");
	if(sock_fd_accepter == -1){
		exit(-1);
	}
	
	// dados do servidor
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	// bind
	bind(sock_fd_accepter, (struct sockaddr*)&server_addr, sizeof(server_addr));
	perror("bind");
	
	// listen
	if(listen(sock_fd_accepter, 10) == -1){
		perror("listen ");
		exit(-1);
	}
	perror("listen ");
	
	
	
	return sock_fd_accepter;
}

void * broadcast_thread(void * arg){
	int broadcast_fifo_read;
	char * buffer = malloc(sizeof(Message));
	Message * msgRcv; 
	
	broadcast_fifo_read = open("/tmp/ToBroadcast", O_RDONLY);
	
	while(!stop_broadcast){
		msgRcv = receive_message(broadcast_fifo_read);
		printf("Starting Broadcast\n");
		broadcast(msgRcv->chat);
		printf("Thread fechada\n");
	}
	
	pthread_exit(NULL);
}

void client_command_handler(user* client, Message * msgRcv){
	Message msgSent;
	char query_limits[MAX_SIZE];
	char * buffer;
	
	switch(msgRcv->type){
			
			///// LOGIN /////
			case LOGIN_ID:
				client->username = malloc(MAX_USERNAME_SIZE*sizeof(char));
				strcpy(client->username, msgRcv->username);
				if(add_element(client)) {
					printf("Failed adding username\n");
					msgSent = create_message(INVALID_ID, NULL);
				}
				else{
					printf("Login Request (%s)\n", msgRcv->username);
					msgSent = create_message(OK_ID, NULL);
					printf("OK enviado\n");
				}
				append_log_status(LOGIN_ID, client->username, NULL);
				send_message(client->sock, msgSent);
				break;
				
			///// DISC /////
			case DISC_ID:
				printf("Disconnect Request\n");
				append_log_status(DISC_ID, client->username, NULL);
				msgSent = create_message(OK_ID, NULL);
				send_message(client->sock, msgSent);
				printf("OK enviado\n");
				client_exit_flag = 1;
				break;
				
			///// CHAT /////
			case CHAT_ID:
				printf("Chat received: %s\n", msgRcv->chat);
				append_log_status(CHAT_ID, client->username, msgRcv->chat);
				msgSent = create_message(OK_ID, NULL);
				send_message(client->sock, msgSent);
				msgSent = create_message(CHAT_ID, msgRcv->chat);
				pthread_mutex_lock(&broadcast_mutex);
					send_to_fifo(broadcast_fifo_write, msgSent);
				pthread_mutex_unlock(&broadcast_mutex);
				printf("OK enviado\n");
				break;
				
			////// QUERY /////	
			case QUERY_ID:
				printf("Query %d-%d received\n", msgRcv->query_id_min, msgRcv->query_id_max);
				sprintf(query_limits, "%d-%d", msgRcv->query_id_min, msgRcv->query_id_max);
				append_log_status(QUERY_ID, client->username, query_limits);				
				msgSent = create_message(OK_ID, NULL);
				send_message(client->sock, msgSent);
				printf("OK enviado\n");
				break;
				
			default:
				break;
			}
}

void admin_command_handler(int sock_fd_admin){
	int admin_exit_flag = 0;
	Message * msgRcv;
	Message msgSent;
	
	while(!admin_exit_flag){
		if(!admin_conected){
			admin_sock = accept(sock_fd_admin, NULL, NULL);
			perror("accept");
			printf("admin just connected\n");
			admin_conected = 1;
		}
		msgRcv = receive_message(admin_sock);
		if(msgRcv->type == QUIT_ID){
			printf("admin QUIT received\n");
			append_log_status(QUIT_ID, NULL, NULL);
			msgSent = create_message(OK_ID, NULL);
			send_message(admin_sock, msgSent);
			printf("OK enviado\n");
			admin_exit_flag = 1;
		}
		if(msgRcv->type == DISC_ID){
			printf("admin DISC received\n");
			append_log_status(DISC_ID, "admin", NULL);
			msgSent = create_message(OK_ID, NULL);
			send_message(admin_sock, msgSent);
			close(admin_sock);
			admin_conected = 0;
			continue;
		}
		if(msgRcv->type == LOG_ID){
			printf("admin LOG received\n");
			append_log_status(LOG_ID, NULL, NULL);
			msgSent = create_message(LOG_RESP_ID, log_to_string());
			send_message(admin_sock, msgSent);
			printf("LOG enviado\n");
		}	
	}
	
	
}

void * client_thread_code(void *arg){
	user * client = (user*)arg;	
	Message * msgRcv;
	
	client_exit_flag = 0;
	while(!client_exit_flag){
		msgRcv = receive_message(client->sock);
		if(msgRcv==NULL) break;
		client_command_handler(client, msgRcv);
		
	}
	 
	remove_element(client);
	printf("Client Disconnected\n");
	close(client->sock);
	pthread_exit(NULL);
}


void * accepter_thread(void*arg){
	int new_sock;
	int accepter_sock;
	user * new_user;
	
	if(access("/tmp/ToBroadcast", F_OK) == -1)
		if(mkfifo("/tmp/ToBroadcast", 0600) != 0)
			perror("broadcast mkfifo");
			
	broadcast_fifo_write = open("/tmp/ToBroadcast", O_WRONLY);
	
	accepter_sock = thread_sock_ini(PORT);
	accepter_exit_flag = 0;
	
	while(!accepter_exit_flag){
		// accept
		new_sock = accept(accepter_sock, NULL, NULL);
		perror("accept");
		new_user = create_user(new_sock);
		// criação de uma thread para cada ligação nova
		pthread_create(&new_user->thread_id, NULL, client_thread_code, new_user);
	}	
	
	pthread_exit(NULL);
	
}

void check_fifo(){
	if(access(FIFO_NAME, F_OK ) == -1 ) {
		if(mkfifo(FIFO_NAME, 0600) != 0 ){
			perror("mkfifo ");
			exit(-1);
		}
	}
}

void * imAlive(void *arg){
	int fd_fifo;
	int tick_time = TICK_TIME;
	int alive = 1;
	
	fd_fifo = openFIFO_server(1);
	while(1){
		sleep(tick_time);
		if(write(fd_fifo, &alive, sizeof(alive)) == -1){
			perror("write");
			exit(-1);
		}else{
			printf("(S)Thread imAlive wrote to FIFO\n");
		}
	}
	
	pthread_exit(NULL);
}

int createRelauncher(){
	int f_ret;
	f_ret = fork();
	char * v[1] = {NULL};
	
	//Fork
	if (!f_ret) // IF SON
		return execve( "relauncher", v , NULL); // Create Process
	else //PARENT
		return f_ret;
}

void * keepRelauncherAlive(void *arg){
	int status;
	int pid_proc;
	
	printf("Starting relauncher...\n");
	createRelauncher();
	while (1){
		pid_proc = wait(&status);
		if(WIFSIGNALED(status)){
			printf("Relauncher parou de excutar PID:(%d) returned with %d code\n", pid_proc, WEXITSTATUS(status));
			printf("Starting relauncher...\n");
			createRelauncher();
		}
		
		
	}
	pthread_exit(NULL);
}

void * isAlive(void *arg){
	int fd_fifo;
	int tick_time = TICK_TIME;
	int alive = 1;
	
	int tol = TOLERANCE;
	int r;
	
	pthread_t thread_imAlive;
	pthread_t thread_keepRelauncherAlive;
	
	fd_fifo = openFIFO_server(0);
	while(1){
		sleep(tick_time);
		r=read(fd_fifo, &alive, sizeof(alive));
		if(r == -1 || r == 0){
			if(r == -1) perror("read");
			if(tol == 0){
				printf("Relauncher is dead!\n");
				break;//Exit from this loop, need to change behaviour of Server
			}else{
				printf("Relauncher may be dead, %d attemp(s) left\n", tol);
				tol--;		
			}
		}else{
			printf("Relauncher is alive\n");
		}
	}
	
	//close fifo (in reading mode)
	close(fd_fifo);
	
	//Server is now handling relauncher execution
	pthread_create(&thread_imAlive, NULL, imAlive, NULL);
	printf("(S) New thread: imAlive\n");

	pthread_create(&thread_keepRelauncherAlive, NULL, keepRelauncherAlive, NULL);
	printf("(S) New thread: KeepRelauncherAlive\n");
	
	sleep(INFINITY);
	
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
	int exit_flag=0;
	int admin_conected=0;
	int sock_fd_admin;
	pthread_t broadcast_thread_id;
	pthread_t accepter;
		
	check_fifo();
	
	if(argc<2){
		pthread_create(&thread_imAlive, NULL, imAlive, NULL);		
		pthread_create(&thread_keepRelauncherAlive, NULL, keepRelauncherAlive, NULL);
	}else{
		pthread_create(&thread_isAlive, NULL, isAlive, NULL);
	}
		
	// criação lista de clientes
	create_list();
	// inicio do log
	log_ini();	
	append_log_status(START_ID, NULL, NULL);
	
	// criação de thread para aceitar ligações
	accepter_exit_flag = 0;
	pthread_create(&accepter, NULL, accepter_thread, NULL);
	// criação de thread de broadcast
	stop_broadcast = 0;
	pthread_create(&broadcast_thread_id, NULL, broadcast_thread, NULL);
	
	
	// para ligação de admin
	admin_conected = 0;
	sock_fd_admin = thread_sock_ini(PORT+1);
	admin_command_handler(sock_fd_admin);

	printf("Shuting down!\n");
	append_log_status(STOP_ID, NULL, NULL);
	
	close(admin_sock);
	destroy_list();
	destroy_log();
	exit(0);

}
