#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <unistd.h>

#define LOGIN_STR "LOGIN"// username 
#define DISC_STR "DISC"
#define CHAT_STR "CHAT"// string
#define QUERY_STR "QUERY"// id_min id_max – request o
 

int main(){
	int should_exit;
	char line[100];
	char command[100];
	char cmd_str_arg[100];
	int cmd_int_arg1, cmd_int_arg2;
	int sock_fd;
	
	struct sockaddr_in server_addr, client_addr;
	
	// criação do socket
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	perror("socket");
	if(sock_fd == -1){
		exit(-1);
	}
	
	// dados do servidor
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(3000);
	inet_aton("127.0.0.1", & server_addr.sin_addr);
	
	// connect
	if( connect(sock_fd, ( struct sockaddr *) &server_addr, sizeof(server_addr)) == -1){
		perror("connect ");
		exit(-1);
	}
	
	should_exit= 0;

	while(! should_exit){
		
		fgets(line, 200, stdin);
		send(sock_fd, line, strlen(line) +1, 0);
		if(sscanf(line, "%s", command) == 1){
			if(strcmp(command, LOGIN_STR) == 0){
				if(sscanf(line, "%*s %s", cmd_str_arg) == 1){
					
						printf("Sending LOGIN command (%s)\n", cmd_str_arg);
				
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
