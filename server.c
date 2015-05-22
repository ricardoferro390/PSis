#include "message.h"
#include <pthread.h>

user * client_list;



void * client_thread_code(void *arg){
	user * client = arg;
	bool exit_flag = 0;
	Message msgSent = MESSAGE__INIT;
	Message * msgRcv;
	char *bufferS;
	char bufferR[MAX_SIZE];
	
	while(!exit_flag){
		msgRcv = receive_message(client->sock);
		
		switch(msgRcv->type){
			case LOGIN_ID:
				// login
				break;
			case DISC_ID:
				// código para disconnect
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
}




int main(){

	int sock_fd, new_sock;
	char bufferR[MAX_SIZE];
	char *bufferS;
	char command[100];
	char cmd_str_arg[100];
	Message * msgRcv;
	Message msgSent = MESSAGE__INIT;

	
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

	// accept
	new_sock = accept(sock_fd, NULL, NULL);
	perror("accept");

	
	msgRcv = receive_message(new_sock);
	printf("Received message:\n\tType %d\n\tData %s\n", msgRcv->type, msgRcv->username);
	
	
		switch (msgRcv->type) {
		case 0:
			if(!add_element(client_list, msgRcv->username)) {
				printf("Failed adding username\n");
				msgSent.type = INVALID_ID;
			}
			else{
				printf("Login Request\n");
				// código para login
				//msgSent.type = OK_ID;
				msgSent = create_message(OK_ID, NULL);
			}
			//msg.has_username = 1;
			send_message(new_sock, msgSent);
			
		
		case DISC_ID:
			// código para disconnect

		case CHAT_ID:
			// código para chat

		case QUERY_ID:
			// código para query
		default:
			break;
		}
		
		
		
		
		
		
	

	exit(0);

}
