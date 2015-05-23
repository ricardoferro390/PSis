#include "ProtoBuffers.pb-c.h"
#include "message.h"
#include "login_list.h"
#include "log.h"

void * broadcast_thread(void * arg){
	char * string = (char*)arg;
	printf("Starting Broadcast\n");
	broadcast(string);
	printf("Thread fechada\n");
	pthread_exit(NULL);
}

void * client_thread_code(void *arg){
	user * client = (user*)arg;	
	int exit_flag = 0;
	Message msgSent;
	Message * msgRcv;
	char *bufferS;
	char bufferR[MAX_SIZE];
	pthread_t thread_id;
	
	while(!exit_flag){
		msgRcv = receive_message(client->sock);
		if(msgRcv==NULL) break;
		printf("mensagem recebida\n");
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
				msgSent = create_message(OK_ID, NULL);
				send_message(client->sock, msgSent);
				printf("OK enviado\n");
				exit_flag = 1;
				break;
				
			///// CHAT /////
			case CHAT_ID:
				printf("Chat received: %s\n", msgRcv->chat);
				msgSent = create_message(OK_ID, NULL);
				send_message(client->sock, msgSent);
				printf("OK enviado\n");
				pthread_create(&thread_id, NULL, broadcast_thread, msgRcv->chat);
				break;
				
				
			case QUERY_ID:
				// código para query
				break;
				
			///// QUIT //////
			case QUIT_ID:
				printf("QUIT received: %s\n", msgRcv->chat);
				msgSent = create_message(OK_ID, NULL);
				send_message(client->sock, msgSent);
				printf("OK enviado\n");
				break;
				
			default:
				break;
			}
	}
	
	remove_element(client);
	close(client->sock);
	printf("Thread fechada\n");
	pthread_exit(NULL);
}

void * accepter_thread(void*arg){

	int exit_flag=0;
	struct sockaddr_in server_addr, client_addr;
	int new_sock, sock_fd;
	user * new_user;
	
	// criação do socket
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	perror("socket");
	if(sock_fd == -1){
		exit(-1);
	}
	
	// dados do servidor
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	// bind
	bind(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	perror("bind");
	
	// criação lista de clientes
	create_list();
	// inicio do log
	log_ini();
	
	// listen
	if(listen(sock_fd, 10) == -1){
		perror("listen ");
		exit(-1);
	}
	perror("listen ");
	
	while(!exit_flag){
		// accept
		new_sock = accept(sock_fd, NULL, NULL);
		perror("accept");
		new_user = create_user(new_sock);
		// criação de uma thread para cada ligação nova
		pthread_create(&new_user->thread_id, NULL, client_thread_code, new_user);
		printf("Novo utilizador aceite! Nova thread criada\n");
	}	
	
	pthread_exit(NULL);
	
}



int main(){
	int exit_flag=0;
	int admin_conected=0;
	struct sockaddr_in server_addr, client_addr;
	int new_sock, sock_fd, admin_sock;
	user * new_user;
	pthread_t accepter;
	Message * msgRcv;
	Message msgSent;
	
	//criação de thread para aceitar ligações
	pthread_create(&accepter, NULL, accepter_thread, NULL);
	
	// criação do socket
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	perror("socket");
	if(sock_fd == -1){
		exit(-1);
	}
	// dados do servidor
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT+1);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	// bind
	bind(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	perror("bind");
	// listen
	if(listen(sock_fd, 10) == -1){
		perror("listen ");
		exit(-1);
	}
	perror("listen ");
		
	while(!exit_flag){
		if(!admin_conected){
			admin_sock = accept(sock_fd, NULL, NULL);
			perror("accept");
			printf("admin just connected\n");
			admin_conected = 1;
		}
		msgRcv = receive_message(admin_sock);
		if(msgRcv->type == QUIT_ID){
			printf("admin QUIT received\n");
			msgSent = create_message(OK_ID, NULL);
			send_message(admin_sock, msgSent);
			printf("OK enviado\n");
			exit_flag = 1;
		}
		if(msgRcv->type == DISC_ID){
			printf("admin DISC received\n");
			msgSent = create_message(OK_ID, NULL);
			send_message(admin_sock, msgSent);
			close(admin_sock);
			admin_conected = 0;
			continue;
		}
		if(msgRcv->type == LOG_ID){
			printf("admin LOG received\n");
			msgSent = create_message(OK_ID, NULL);
			send_message(admin_sock, msgSent);
			printf("OK enviado\n");
		}
		
	}
	
	printf("Admin command receiver! Shuting down...\n");
	close(admin_sock);
	destroy_list();
	destroy_log();
	exit(0);

}
