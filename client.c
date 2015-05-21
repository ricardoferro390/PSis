#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "ProtoBuffers.pb-c.h"

#define LOGIN_STR "LOGIN"// username 
#define DISC_STR "DISC"
#define CHAT_STR "CHAT"// string
#define QUERY_STR "QUERY"// id_min id_max – request o
#define MAX_SIZE 1024

#define LOGIN_ID 0
#define DISC_ID 1
#define CHAT_ID 2
#define QUERY_ID 3
#define OK_ID 4
#define INVALID_ID 5
 
int main(){
	int should_exit;
	char line[100];
	char command[100];
	char cmd_str_arg[100];
	int cmd_int_arg1, cmd_int_arg2;
	int sock_fd;
	
	Message msgSent = MESSAGE__INIT;
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
	server_addr.sin_port = htons(3001);
	inet_aton("127.0.0.1", & server_addr.sin_addr);
	
	// connect
	if( connect(sock_fd, ( struct sockaddr *) &server_addr, sizeof(server_addr)) == -1){
		perror("connect ");
		exit(-1);
	}
	
	should_exit= 0;

	while(! should_exit){
			
		fgets(line, 200, stdin);
		if(sscanf(line, "%s", command) == 1){
			if(strcmp(command, LOGIN_STR) == 0){
				
				if(sscanf(line, "%*s %s", cmd_str_arg) == 1){
					msgSent.type = LOGIN_ID;
					msgSent.username = strdup(cmd_str_arg);
					//msg.has_username = 1;
					bufferS = malloc(message__get_packed_size(&msgSent));
					message__pack(&msgSent, bufferS);
					send(sock_fd, bufferS, message__get_packed_size(&msgSent), 0);
					printf("Sending LOGIN command (%s)\n", cmd_str_arg);
					
					// receber resposta OK
					size_t len = read(sock_fd, bufferR, MAX_SIZE);
					msgRcv = message__unpack(NULL, len, bufferR);
					if(msgRcv->type==OK_ID) printf("Received OK\n");
					should_exit = 1;
				}
				
				else{
					printf("Invalid LOGIN command\n");
				}
			}else if(strcmp(command, DISC_STR)==0){
					send(sock_fd, command, strlen(command) +1, 0);
					printf("Sending DISconnnect command\n");
					close(sock_fd);
					printf("Connection closed");
										
					
					
			}else if(strcmp(command, CHAT_STR)==0){
				if(sscanf(line, "%*s %s", cmd_str_arg) == 1){
				
						printf("Sending CHAT command (%s)\n", cmd_str_arg);
				
				
				}
				else{
					printf("Invalid CHAT command\n");
				}
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
	
	
	
	
	exit(0);
}
