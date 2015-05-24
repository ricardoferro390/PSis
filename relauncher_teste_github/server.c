#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/stat.h>

#define SEND_TIME 2


int i = 0;

int openFIFO(){
	int fd_fifo;
	
	fd_fifo = open("/tmp/fifo_alive", O_RDONLY);
	if(fd_fifo == -1){
		perror("open");
		exit(-1);
	}
	sync();
	printf("Opened FIFO\n");
	return fd_fifo;

}

void * thread_code(void *arg){
	int value = *((int *)arg);
	
	while(1){
		sleep(value);
		printf("Thread %d %d\n", value, i);
		i++;
	}
	pthread_exit(NULL);
}


void * thread_read_code(void *arg){
	int *alive = ((int *)arg);
	int fd_fifo = openFIFO();
	int a = 0;
	
	while(1){
		read(fd_fifo, &a, sizeof(a));
		printf("Just Read - Parent is Alive\n");
		*alive = 1;
	}
	pthread_exit(NULL);
}

void * thread_check_code(void *arg){
	int *alive = ((int *)arg);
	char * v[1] = {NULL};
	
	int check_time = SEND_TIME*2;
	
	while(1){
		sleep(check_time);
		if (*alive == 1){
			printf("Read Alive, it is %d\n", *alive);
			*alive = 0;
		}else{
			execve( "parent", v , NULL);
			exit(0);
		}
	}
	pthread_exit(NULL);
}
			

typedef struct user_list {
	char	user_name[50];
	int 	sock;
	pthread_t thread_id;
} user_list;


int main(){
	pthread_t thread_id_1;
	pthread_t thread_id_2;
	pthread_t thread_read;
	pthread_t thread_check;
	void * res;
	int arg_1;
	int arg_2;
	int alive = 0;
	int *alive_ptr = &alive;
	
	arg_1 = 1;
	pthread_create(&thread_id_1, NULL, thread_code, &arg_1);
	printf("New thread %d\n", (int) thread_id_1);

	arg_2 = 2;	
	pthread_create(&thread_id_2, NULL, thread_code, &arg_2);
	printf("New thread %d\n", (int) thread_id_2);
	
	pthread_create(&thread_read, NULL, thread_read_code, alive_ptr);
	printf("New thread - Thread Read\n");
	
	pthread_create(&thread_check, NULL, thread_check_code, alive_ptr);
	printf("New thread - Thread Check\n");

	getchar();

	pthread_join(thread_id_1, &res);
	pthread_join(thread_id_2, &res);
	pthread_join(thread_read, &res);
	pthread_join(thread_check, &res);
	exit(0);
}
