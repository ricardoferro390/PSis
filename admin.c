#include "message.h"

int main(int argc, char * argv[]){
	int should_exit = 0;
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
	server_addr.sin_port = htons(PORT+1);
	inet_aton("127.0.0.1", & server_addr.sin_addr);
	
	// connect
	if( connect(sock_fd, ( struct sockaddr *) &server_addr, sizeof(server_addr)) == -1){
		perror("connect ");
		exit(-1);
	}
	
	/*FD_ZERO(&socks);
	FD_SET(sock_fd, &socks);
	FD_SET(0, &socks);*/
	

	while(!should_exit){
		//select(sock_fd+1, &socks, NULL, NULL, NULL);

		/*if (FD_ISSET(sock_fd, &socks)){

			msgRcv = receive_message(sock_fd);
			if(msgRcv->type==CHAT_ID) printf("Received chat:\t%s\n", msgRcv->chat);
			
        }
		
		else if (FD_ISSET(0, &socks)){*/

			fgets(line, 200, stdin);
			if(sscanf(line, "%s", command) == 1){
				
				///////// LOG admin /////////
				if(strcmp(command, LOG_STR)==0){
					msgSent = create_message(LOG_ID, NULL);
					send_message(sock_fd, msgSent);
					printf("Sending LOG command\n");
					msgRcv = receive_message(sock_fd);
					if(msgRcv->type==OK_ID) printf("Received OK %d\n", msgRcv->type);
				}
				
				////////// DISC /////////	
				else if(strcmp(command, DISC_STR)==0){
					msgSent = create_message(DISC_ID, NULL);
					send_message(sock_fd, msgSent);
					printf("Sending DISconnnect command\n");
					msgRcv = receive_message(sock_fd);
					//printf("recebi\n");
					if(msgRcv->type==OK_ID) printf("Received OK %d\n", msgRcv->type);
					if(msgRcv->type==OK_ID){
						should_exit = 1;
					}
				}
															
				///////// QUIT admin /////////
				else if(strcmp(command, QUIT_STR)==0){
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
	printf("Admin terminated\n");
	exit(0);
}
	


