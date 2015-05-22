#include "message.h"

int main(){
	int should_exit = 0;
	int login_made = 0;
	char line[100];
	char command[100];
	char cmd_str_arg[100];
	int cmd_int_arg1, cmd_int_arg2;
	int sock_fd;
	
	Message msgSent;
	Message * msgRcv;
	char *bufferS;
	char bufferR[MAX_SIZE];
	unsigned len;
	
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
	inet_aton("127.0.0.1", & server_addr.sin_addr);
	
	// connect
	if( connect(sock_fd, ( struct sockaddr *) &server_addr, sizeof(server_addr)) == -1){
		perror("connect ");
		exit(-1);
	}

	while(!should_exit){
			
		fgets(line, 200, stdin);
		if(sscanf(line, "%s", command) == 1){
			
			////////// LOGIN /////////
			if(strcmp(command, LOGIN_STR) == 0){
				if(!login_made){	
					if(sscanf(line, "%*s %s", cmd_str_arg) == 1){
						msgSent = create_message(LOGIN_ID, cmd_str_arg);
											
						send_message(sock_fd, msgSent);
						
						printf("Sending LOGIN command (%s)\n", cmd_str_arg);
						
						// receber resposta OK
						msgRcv = receive_message(sock_fd);
						if(msgRcv->type==OK_ID){
							printf("Received OK %d\n", msgRcv->type);
							login_made = 1;
						}
						if(msgRcv->type==INVALID_ID) printf("Invalid Login\n");
					}
					
					else{
						printf("Invalid LOGIN command\n");
					}
				}else printf("Login already made!\n");
			
			
			////////// DISC /////////	
			}else if(strcmp(command, DISC_STR)==0){
					msgSent = create_message(DISC_ID, NULL);
					send_message(sock_fd, msgSent);
					printf("Sending DISconnnect command\n");
					msgRcv = receive_message(sock_fd);
					if(msgRcv->type==OK_ID) printf("Received OK %d\n", msgRcv->type);
					if(msgRcv->type==OK_ID){
						should_exit = 1;
					}
						
											
						
			////////// CHAT /////////			
			}else if(strcmp(command, CHAT_STR)==0){
				if(sscanf(line, "%*s %s", cmd_str_arg) == 1){
				
						printf("Sending CHAT command (%s)\n", cmd_str_arg);
				
				
				}
				else{
					printf("Invalid CHAT command\n");
				}
				
			////////// QUERY /////////
			}else if(strcmp(command, QUERY_STR)==0){
				if(sscanf(line, "%*s %d %d", &cmd_int_arg1, &cmd_int_arg2) == 2){
				
						printf("Sending QUERY command (%d %d)\n", cmd_int_arg1, cmd_int_arg2);
				
				}
				else{
					printf("Invalid QUERY command\n");
				}
					
					
					
					
					
			}else{
				printf("Invalid command\n");
			}
		}else{
			printf("Error in command\n");
		}
		
	}
	
	
	close(sock_fd);
	printf("Client terminated");
	exit(0);
}
