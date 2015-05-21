#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
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
	server_addr.sin_port = htons(3001);
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

	// accept
	new_sock = accept(sock_fd, NULL, NULL);
	perror("accept");

	size_t len = read(new_sock, bufferR, MAX_SIZE);
	msgRcv = message__unpack(NULL, len, bufferR);
	printf("Received message:\n\tType %d\n\tData %s\n", msgRcv->type, msgRcv->username);
	
		switch (msgRcv->type) {
		case 0:
			printf("Login Request\n");
			
			msgSent.type = OK_ID;
			bufferS = malloc(message__get_packed_size(&msgSent));
			send(new_sock, bufferS, message__get_packed_size(&msgSent), 0);
			// código para login
		
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
