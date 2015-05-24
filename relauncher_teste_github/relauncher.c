#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include <string.h>

#define TICK_TIME 5
#define TOLERANCE 3

int openFIFO(int mode){
	int fd_fifo=-1;
	
	if (mode==0){
		fd_fifo = open("/tmp/heartbeat_of_DOOOM_from_the_PURGATORY_OF_DARKEST_of_the_ROTTEN_HELLS_OF_HADES_YEAAAHH_fifo", O_RDONLY|O_NONBLOCK);
	}else if(mode==1){
		fd_fifo = open("/tmp/heartbeat_of_DOOOM_from_the_PURGATORY_OF_DARKEST_of_the_ROTTEN_HELLS_OF_HADES_YEAAAHH_fifo", O_WRONLY);
	}
	
	if(fd_fifo == -1){
		perror("open");
		exit(-1);
	}
	sync();
	printf("Opened FIFO (Relauncher)\n");
	
	return fd_fifo;
}
	
void * imAlive(void* arg){
	int fd_fifo;
	int tick_time = TICK_TIME;
	int alive = 1;
	
	fd_fifo = openFIFO(1);
	while(1){
		sleep(tick_time);
		if(write(fd_fifo, &alive, sizeof(alive)) == -1){
			perror("write");
			exit(-1);
		}else{
			printf("(R)Thread imAlive wrote to FIFO\n");
		}
	}
	
	pthread_exit(NULL);
}

int createServer(){
	int f_ret;
	char * v[] = {"svr","1",NULL};	//execute server without relauncher
	
	//Fork
	f_ret = fork();
	if (!f_ret) //son
		return execve("svr", v , NULL); // Create Process
	else //parent
		return f_ret;
}

void * keepServerAlive(void* arg){
	int status;
	int pid_proc;
	
	printf("Starting server...\n");
	createServer();
	while (1){
		pid_proc = wait(&status);
		if(WIFSIGNALED(status)){
			printf("Server stopped PID:(%d) returned with %d code\n", pid_proc, WEXITSTATUS(status));
			printf("Starting server...\n");
			createServer();
		}
	}
	pthread_exit(NULL);
}

void * isAlive(void *arg){
	int fd_fifo;
	int tick_time = TICK_TIME;
	int alive = 1;
	
	int tol = TOLERANCE;
	int r;
	
	pthread_t thread_imAlive;
	pthread_t thread_keepServerAlive;
	
	//printf("Attempting to open FIFO (Relauncher)\n");
	fd_fifo = openFIFO(0);
	while(1){
		sleep(tick_time);
		printf("Attempting to read FIFO (Relauncher)\n");
		r=read(fd_fifo, &alive, sizeof(alive));
		if(r == -1){
			perror("read");
			if(tol == 0){
				printf("Server is dead!\n");
				break;//Exit from this loop, need to change behaviour of Relauncher
			}else{
				printf("Server may be dead, %d attemp(s) left\n", tol);
				tol--;		
			}
		}else if(r == 0){
			if(tol == 0){
				printf("Server is dead!\n");
				break;//Exit from this loop, need to change behaviour of Relauncher
			}else{
				printf("Server may be dead, %d attemp(s) left\n", tol);
				tol--;		
			}		
		}else{
			printf("Server is alive\n");
		}
	}
	
	//close fifo (in reading mode)
	close(fd_fifo);
	
	//Relauncher is now handling server execution
	pthread_create(&thread_imAlive, NULL, imAlive, NULL);
	printf("(R) New thread: imAlive\n");

	pthread_create(&thread_keepServerAlive, NULL, keepServerAlive, NULL);
	printf("(R) New thread: KeepServerAlive\n");
	
	while(1) sleep(3600);
	
	pthread_exit(NULL);
}


int main(int argc, char **argv)
{
	pthread_t thread_isAlive;
	
	if( access("/tmp/heartbeat_of_DOOOM_from_the_PURGATORY_OF_DARKEST_of_the_ROTTEN_HELLS_OF_HADES_YEAAAHH_fifo", F_OK ) == -1 ) {
		if (mkfifo("/tmp/heartbeat_of_DOOOM_from_the_PURGATORY_OF_DARKEST_of_the_ROTTEN_HELLS_OF_HADES_YEAAAHH_fifo", 0600) != 0 ){
			perror("mkfifo ");
			exit(-1);
		}
	}
		
	printf("Relauncher!\n");
	//printf("Server PID:(%d) My PID:(%d)\n", getppid(), getpid());
	
	pthread_create(&thread_isAlive, NULL, isAlive, NULL);
	printf("(R) New thread - Thread isAlive\n");
	
	while(1) sleep(3600);
	
	return 0;
}

