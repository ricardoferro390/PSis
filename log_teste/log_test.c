#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <time.h>


#define MAX_SIZE 1024

/*retirado de
http://www.cplusplus.com/reference/ctime/localtime/
*/
char* get_current_time(){
	char* time_str;
	time_str = malloc(30*sizeof(char));
	time_t rawtime;
	struct tm * timeinfo;
	
	if(time_str!=NULL){
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		time_str = asctime(timeinfo);
	}
	
	return time_str;
}

void append_log_status(FILE * log_fd, int status){
	//status indica o tipo de operacao do servidor a registar
	//type=0 -> Servidor arranca normalmente
	//type=1 -> Servidor parou inesperadamente
	//type=2 -> Servidor recuperou
	
	char* status_str;
	char* time_str;
	
	status_str = malloc(30*sizeof(char));
	if(status_str == NULL) return;
	switch (status){
		case (0):
			strcpy(status_str,"Inicio do servidor:");
			break;
		case (1):
			strcpy(status_str,"Paragem do servidor:");
			break;
		case (2):
			strcpy(status_str,"Recuperacao do servidor:");
			break;
		default:
			return;
		}
	time_str = get_current_time();
	fprintf(log_fd,"%s %s",status_str,time_str);
	
	return;
}

void append_log_message(FILE * log_fd, int id, char* message){
	fprintf(log_fd, "%d %s", id, message);
	return;
}


int main(){
	FILE * log_fd;
	log_fd = fopen("teste.log","a");

	append_log_status(log_fd,0);
	append_log_status(log_fd,1);
	append_log_status(log_fd,2);
	
	append_log_status(log_fd,3);
	
	return 0;
}
