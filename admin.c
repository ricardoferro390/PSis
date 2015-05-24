#include "ProtoBuffers.pb-c.h"
#include "message.h"

int sock;
int should_exit;

void admin_ini(){
	struct sockaddr_in server_addr, client_addr;
	
	// criação do socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	perror("socket");
	if(sock == -1){
		exit(-1);
	}
	
	// dados do servidor
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT+1);
	inet_aton("127.0.0.1", & server_addr.sin_addr);
	
	// connect
	if( connect(sock, ( struct sockaddr *) &server_addr, sizeof(server_addr)) == -1){
		perror("connect ");
		exit(-1);
	}
	
	should_exit = 0;

}

void command_handler(){
	char command[100];
	char cmd_str_arg[100];
	char line[100];
	int cmd_int_arg1, cmd_int_arg2;
	Message msgSent;
	Message * msgRcv;
	
	fgets(line, 200, stdin);
	if(sscanf(line, "%s", command) == 1){
				
				///////// LOG admin /////////
				if(strcmp(command, LOG_STR)==0){
					msgSent = create_message(LOG_ID, NULL);
					send_message(sock, msgSent);
					printf("Sending LOG command\n");
					msgRcv = receive_message(sock);
					if(msgRcv->type==LOG_RESP_ID) printf("%s\n", msgRcv->log_resp);
				}
				
				////////// DISC /////////	
				else if(strcmp(command, DISC_STR)==0){
					msgSent = create_message(DISC_ID, NULL);
					send_message(sock, msgSent);
					printf("Sending DISconnnect command\n");
					msgRcv = receive_message(sock);
					//printf("recebi\n");
					if(msgRcv->type==OK_ID) printf("Received OK %d\n", msgRcv->type);
					if(msgRcv->type==OK_ID){
						should_exit = 1;
					}
				}
															
				///////// QUIT admin /////////
				else if(strcmp(command, QUIT_STR)==0){
					msgSent = create_message(QUIT_ID, NULL);
					send_message(sock, msgSent);
					printf("Sending QUIT command\n");
					msgRcv = receive_message(sock);
					if(msgRcv->type==OK_ID) printf("Received OK %d\n", msgRcv->type);
					if(msgRcv->type==OK_ID){
						should_exit = 1;
					}
				}
			}
}


int main(int argc, char * argv[]){
	fd_set fd;
	admin_ini();
	
	while(!should_exit){
			command_handler();	
	}
	close(sock);
	printf("Good Bye Chief!\n");
	exit(0);
}
	


