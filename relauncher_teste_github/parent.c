#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <pthread.h>
#define SEND_TIME 2

int createSon(){
	int f_ret;
	f_ret = fork();
	char * v[1] = {NULL};
	
	//Fork
	if (!f_ret) // IF SON
		return execve( "server", v , NULL); // Create Process
	else //PARENT
		return f_ret;
}

int openFIFO(){
	int fd_fifo;
	
	fd_fifo = open("/tmp/fifo_alive", O_WRONLY);
	if(fd_fifo == -1){
		perror("open");
		exit(-1);
	}
	sync();
	printf("Opened FIFO\n");
	return fd_fifo;

}


void * isAlive(void *arg){
	int value = *((int *)arg);
	int alive = 1;
	int fd_fifo = openFIFO();
	
	while(1){
		sleep(value);
		if( write(fd_fifo, &alive, sizeof(alive)) == -1){
			perror("write");
			exit(-1);
		}else{
			printf("Thread isAlive Sending to FIFO\n");
		}
	}
	pthread_exit(NULL);
}

void * keepSonAlive(void *arg){
	int status;
	int pid_proc;
	
	createSon();
	while (1){
		pid_proc = wait(&status);
		if(WIFSIGNALED(status)){
			printf("parent my child (%d) returned with %d code\n", pid_proc, WEXITSTATUS(status));
			createSon();
		}
	}
	
	pthread_exit(NULL);
}



int main(){
	pthread_t thread_isAlive;
	pthread_t thread_keepSonAlive;
	void * res;
	
	if( access("/tmp/fifo_alive", F_OK ) == -1 ) {
		if (mkfifo("/tmp/fifo_alive", 0600) != 0 ){
			perror("mkfifo ");
			exit(-1);
		}
	}
	
	
	
	printf("Parent Starting\n");
	printf("parent (%d)\nprocess(%d)\n", getppid(), getpid());
	
	int send_time = SEND_TIME;
	pthread_create(&thread_isAlive, NULL, isAlive, &send_time);
	printf("New thread - isAlive Created\n");
	
	pthread_create(&thread_keepSonAlive, NULL, keepSonAlive, NULL);
	printf("New thread - keepSonAlive Created\n");
	
	
	getchar();

	pthread_join(thread_isAlive, &res);
	pthread_join(thread_keepSonAlive, &res);
	exit(0);
}	
