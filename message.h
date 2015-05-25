#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "ProtoBuffers.pb-c.h"

#define LOGIN_STR "LOGIN"// username 
#define DISC_STR "DISC"
#define CHAT_STR "CHAT"// string
#define QUERY_STR "QUERY"// id_min id_max – request o
#define QUIT_STR "QUIT"
#define LOG_STR "LOG"
#define START_STR "Server Started"
#define STOP_STR "Server Stoped"
#define RECUP_STR "Server Recuperated"

#define MAX_SIZE 2000000

#define PORT 3000

#define LOGIN_ID 0
#define DISC_ID 1
#define CHAT_ID 2
#define QUERY_ID 3
#define QUERY_RESP_ID 31
#define OK_ID 4
#define INVALID_ID 5
#define QUIT_ID 6
#define LOG_ID 7
#define LOG_RESP_ID 71
#define START_ID 100
#define STOP_ID 101
#define RECUP_ID 102

#define max( a, b) ( ((a) > (b)) ? (a) : (b) )

void send_message(int sock, Message msg);
Message * receive_message(int sock);
Message create_message(int type, char* string);
int send_to_fifo(int fifo_fd, Message msg);
Message * receive_from_fifo(int fifo_fd);
