#include "ProtoBuffers.pb-c.h"
#include "message.h"
#include "login_list.h"
#include "log.h"

int client_exit_flag, accepter_exit_flag;
int admin_sock, accepter_sock;
int admin_conected;

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
	char * string = (char*)arg;
	printf("Starting Broadcast\n");
	broadcast(string);
	printf("Thread fechada\n");
	pthread_exit(NULL);
}

void client_command_handler(user* client, Message * msgRcv){
	Message msgSent;
	pthread_t broadcast_thread_id;
	char query_limits[MAX_SIZE];
	
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
				printf("OK enviado\n");
				//pthread_create(&broadcast_thread_id, NULL, broadcast_thread, msgRcv->chat);
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
			msgSent = create_message(OK_ID, NULL);
			send_message(admin_sock, msgSent);
			printf("OK enviado\n");
		}	
	}
	
	
}

void * client_thread_code(void *arg){
	user * client = (user*)arg;	
	Message * msgRcv;
	
	
	client_exit_flag = 0;
	while(!client_exit_flag){
		msgRcv = receive_message(client->sock);
		if(msgRcv==NULL) continue;
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


int main(){
	int exit_flag=0;
	int admin_conected=0;
	int sock_fd_admin;

	pthread_t accepter;	
	
	append_log_status(START_ID, NULL, NULL);
	
	// criação lista de clientes
	create_list();
	
	// inicio do log
	log_ini();	
	
	//criação de thread para aceitar ligações
	pthread_create(&accepter, NULL, accepter_thread, NULL);
	
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
