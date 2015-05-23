#include "message.h"

int main(int argc, char * argv[]){
	int should_exit = 0;
	int login_made = 0;
	int admin = 0;
	char line[100];
	char command[100];
	char cmd_str_arg[100];
	int cmd_int_arg1, cmd_int_arg2;
	int sock_fd;
	fd_set socks;
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
	//se for admin
	if(argc==2 && strcmp(argv[1], "admin")==0){
		server_addr.sin_port = htons(PORT+1);
		admin = 1;}
	else{
		server_addr.sin_port = htons(PORT);
	}
	inet_aton("127.0.0.1", & server_addr.sin_addr);
	
	// connect
	if( connect(sock_fd, ( struct sockaddr *) &server_addr, sizeof(server_addr)) == -1){
		perror("connect ");
		exit(-1);
	}
	
	/*FD_ZERO(&socks);
	FD_SET(sock_fd, &socks);
	FD_SET(0, &socks);
*/
	

	while(!should_exit){
		//select(sock_fd+1, &socks, NULL, NULL, NULL);

		/*if (FD_ISSET(sock_fd, &socks)){

			msgRcv = receive_message(sock_fd);
			if(msgRcv->type==CHAT_ID) printf("Received chat:\t%s\n", msgRcv->chat);
			
        }
		
		else if (FD_ISSET(0, &socks)){*/

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
						if(login_made){	
							msgSent = create_message(CHAT_ID, cmd_str_arg);				
							send_message(sock_fd, msgSent);
							printf("Sending CHAT command (%s)\n", cmd_str_arg);
							msgRcv = receive_message(sock_fd);
							if(msgRcv->type==OK_ID) printf("Received OK %d\n", msgRcv->type);
							if(msgRcv->type==INVALID_ID) printf("Invalid Login\n");
						}
						else printf("Please LOGIN first\n");
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

				
				///////// QUIT admin /////////
				}else if(strcmp(command, QUIT_STR)==0 && admin==1){
						printf("Entering QUIT command\n");
						msgSent = create_message(QUIT_ID, NULL);
						send_message(sock_fd, msgSent);
						printf("Sending QUIT command\n");
						msgRcv = receive_message(sock_fd);
						if(msgRcv->type==OK_ID) printf("Received OK %d\n", msgRcv->type);
						if(msgRcv->type==OK_ID){
							should_exit = 1;
						}
				}
		}
	}
	close(sock_fd);
	printf("Client terminated\n");
	exit(0);
}
	

