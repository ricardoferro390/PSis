#include "message.h"
#include <time.h>

#define START_STR "Server Started"
#define STOP_STR "Server Stoped"
#define RECUP_STR "Server Recuperated"

#define START_ID 100
#define STOP_ID 101
#define RECUP_ID 102

#define MAX_SIZE 1024

char * get_current_time();
void log_ini();
int append_log_status(int event_id, char * event_extra_string, char * chat_or_query_string);
void destroy_log();
