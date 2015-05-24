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
	printf("Opened FIFO (Server)\n");
	
	return fd_fifo;
}

void * imAlive(void *arg){
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
			printf("(S)Thread imAlive wrote to FIFO\n");
		}
	}
	
	pthread_exit(NULL);
}

int createRelauncher(){
	int f_ret;
	f_ret = fork();
	char * v[1] = {NULL};
	
	//Fork
	if (!f_ret) // IF SON
		return execve( "relauncher", v , NULL); // Create Process
	else //PARENT
		return f_ret;
}

void * keepRelauncherAlive(void *arg){
	int status;
	int pid_proc;
	
	printf("Starting relauncher...\n");
	createRelauncher();
	while (1){
		pid_proc = wait(&status);
		if(WIFSIGNALED(status)){
			printf("Relauncher parou de excutar PID:(%d) returned with %d code\n", pid_proc, WEXITSTATUS(status));
			printf("Starting relauncher...\n");
			createRelauncher();
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
	pthread_t thread_keepRelauncherAlive;
	
	fd_fifo = openFIFO(0);
	while(1){
		sleep(tick_time);
		r=read(fd_fifo, &alive, sizeof(alive));
		if(r == -1){
			perror("read");
			if(tol == 0){
				printf("Relauncher is dead!\n");
				break;//Exit from this loop, need to change behaviour of Server
			}else{
				printf("Relauncher may be dead, %d attemp(s) left\n", tol);
				tol--;		
			}
		}else if(r == 0){
			if(tol == 0){
				printf("Relauncher is dead!\n");
				break;//Exit from this loop, need to change behaviour of Server
			}else{
				printf("Relauncher may be dead, %d attemp(s) left\n", tol);
				tol--;		
			}
		}else{
			printf("Relauncher is alive\n");
		}
	}
	
	//close fifo (in reading mode)
	close(fd_fifo);
	
	//Server is now handling relauncher execution
	pthread_create(&thread_imAlive, NULL, imAlive, NULL);
	printf("(S) New thread: imAlive\n");

	pthread_create(&thread_keepRelauncherAlive, NULL, keepRelauncherAlive, NULL);
	printf("(S) New thread: KeepRelauncherAlive\n");
	
	while(1) sleep(3600);
	
	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	//pthread_t thread_imAlive;
	//pthread_t thread_keepRelauncherAlive;
	//pthread_t thread_isAlive;
	
	FILE *fd;
	
	if( access("/tmp/heartbeat_of_DOOOM_from_the_PURGATORY_OF_DARKEST_of_the_ROTTEN_HELLS_OF_HADES_YEAAAHH_fifo", F_OK ) == -1 ) {
		if (mkfifo("/tmp/heartbeat_of_DOOOM_from_the_PURGATORY_OF_DARKEST_of_the_ROTTEN_HELLS_OF_HADES_YEAAAHH_fifo", 0600) != 0 ){
			perror("mkfifo ");
			exit(-1);
		}
	}
	
	
	if(argc<2){
		pthread_t thread_imAlive;
		pthread_t thread_keepRelauncherAlive;
		
		printf("Default Server Execution (with handling of relauncher)\n");
		
		fd=fopen("server.log","a");
		fprintf(fd,"Server lauched by bash\n");
		fclose(fd);
		
		pthread_create(&thread_imAlive, NULL, imAlive, NULL);
		printf("(S)New thread: imAlive\n");
		
		
		pthread_create(&thread_keepRelauncherAlive, NULL, keepRelauncherAlive, NULL);
		printf("(S) New thread: KeepRelauncherAlive\n");
		
		while(1) sleep(3600);
	}
	else{
		pthread_t thread_isAlive;
		printf("Relaunched Server Execution (called by relauncher)\n");
		
		fd=fopen("server.log","a");
		fprintf(fd,"Server lauched by relauncher\n");
		fclose(fd);
		
		pthread_create(&thread_isAlive, NULL, isAlive, NULL);
		printf("(S) New thread: isAlive\n");
		
		while(1) sleep(3600);
	}
	
	
	return 0;
}

