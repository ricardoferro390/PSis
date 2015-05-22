#include "message.h"

user * client_list;

void * client_thread_code(void *arg){
	user * client = (user*)arg;
	
	printf("client socket = %d", client->sock);
	
	int exit_flag = 0;
	Message msgSent;
	Message * msgRcv;
	char *bufferS;
	char bufferR[MAX_SIZE];
	
	while(!exit_flag){
		msgRcv = receive_message(client->sock);
		printf("mensagem recebida\n");
		switch(msgRcv->type){
			case LOGIN_ID:
				/*if(!add_element(client_list, client, msgRcv->username)) {
				printf("Failed adding username\n");
				msgSent = create_message(INVALID_ID, NULL);
				}
				else{*/
				printf("Login Request (%s)\n", msgRcv->username);
				msgSent = create_message(OK_ID, NULL);
				//}
				send_message(client->sock, msgSent);
				printf("OK enviado\n");
				break;
			case DISC_ID:
				printf("Disconnect Request\n");
				msgSent = create_message(DISC_ID, NULL);
				send_message(client->sock, msgSent);
				printf("OK enviado\n");
				close(client->sock);
				exit_flag = 1;
				break;
			case CHAT_ID:
				// código para chat
				break;
			case QUERY_ID:
				// código para query
			default:
				break;
			}
	}
	printf("thread fechada");
	pthread_exit(NULL);
}

int main(){
	int exit_flag=0;
	int sock_fd, new_sock;
	char bufferR[MAX_SIZE];
	char *bufferS;
	char command[100];
	char cmd_str_arg[100];
	Message * msgRcv;
	Message msgSent = MESSAGE__INIT;
	user * new_user;
	struct sockaddr_in server_addr, client_addr;
	
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
	client_list = create_list();
	
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
		printf("criei novo utilizador %d\n", new_user->sock);
		pthread_create(&new_user->thread_id, NULL, client_thread_code, new_user);
		printf("NOVO utilizador ligado! thread criada\n");
		
	}	

	exit(0);

}
