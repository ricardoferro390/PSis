#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "ProtoBuffers.pb-c.h"
#include "login_list.h"

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


