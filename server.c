#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){

	int sock_fd, new_sock;
	char buffer[100];
	
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

		read(new_sock, buffer, 200);
		printf("read message %s\n", buffer);
		
		
	

exit(0);

}
