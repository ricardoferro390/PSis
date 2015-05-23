#include "ProtoBuffers.pb-c.h"
#include "message.h"

int sock;
char line[100];
int login_made;
int should_exit;

void client_ini(){
	struct sockaddr_in server_addr, client_addr;
	
	// criação do socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	perror("socket");
	if(sock == -1){
		exit(-1);
	}
	
	// dados do servidor
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	inet_aton("127.0.0.1", & server_addr.sin_addr);
	
	// connect
	if( connect(sock, ( struct sockaddr *) &server_addr, sizeof(server_addr)) == -1){
		perror("connect ");
		exit(-1);
	}
	
	login_made = 0;
	should_exit = 0;

}

void command_handler(){
	char command[100];
	char cmd_str_arg[100];
	int cmd_int_arg1, cmd_int_arg2;
	Message msgSent;
	Message * msgRcv;
	
	if(sscanf(line, "%s", command) == 1){
		
		////////// LOGIN /////////
		if(strcmp(command, LOGIN_STR) == 0){
			if(!login_made){	
				if(sscanf(line, "%*s %s", cmd_str_arg) == 1){
					// envia login
					msgSent = create_message(LOGIN_ID, cmd_str_arg);
					send_message(sock, msgSent);
					printf("Sending LOGIN command (%s)\n", cmd_str_arg);
					// receber resposta OK
					msgRcv = receive_message(sock);
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
				send_message(sock, msgSent);
				printf("Sending DISconnnect command\n");
				msgRcv = receive_message(sock);
				if(msgRcv->type==OK_ID) printf("Received OK %d\n", msgRcv->type);
				if(msgRcv->type==OK_ID){
					should_exit = 1;
				}
												
		////////// CHAT /////////			
		}else if(strcmp(command, CHAT_STR)==0){
			if(sscanf(line, "%*s %s", cmd_str_arg) == 1){
				if(login_made){	
					msgSent = create_message(CHAT_ID, cmd_str_arg);				
					send_message(sock, msgSent);
					printf("Sending CHAT command (%s)\n", cmd_str_arg);
					msgRcv = receive_message(sock);
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


		}
		else printf("Invalid command\n");
	}
}


int main(int argc, char * argv[]){

	client_ini();
	
	while(!should_exit){
		fgets(line, 200, stdin);
		command_handler();
	}
		
	close(sock);
	printf("Good Bye!\n");
	exit(0);
}
	

