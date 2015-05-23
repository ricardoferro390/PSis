include "log.h"

FILE * log_file;
pthread_mutex_t log_mutex;

/*retirado de
http://www.cplusplus.com/reference/ctime/localtime/*/
char * get_current_time(){
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

void log_ini(){
	pthread_mutex_init(&log_mutex, NULL);
	return;
}

int append_log_status(int event_id, char * event_extra_string, char * chat_or_query_string){
	
	char* event_str;
	char* aditional_str;
	char* chat_or_query_str;
	char* time_str;
	
	event_str = malloc(MAX_SIZE*sizeof(char));
	aditional_str = malloc(MAX_SIZE*sizeof(char));
	chat_or_query_str = malloc(MAX_SIZE*sizeof(char));
	if(event_extra_string!=NULL) strcpy(aditional_str, event_extra_string);
	if(chat_or_query_string!=NULL) strcpy(chat_or_query_str, chat_or_query_string);
	if(event_str == NULL || aditional_str == NULL || chat_or_query_str == NULL) return 1;
	
	switch(event_id){
		case LOGIN_ID:
			sprintf(event_str,"LOGIN (user:%s)", aditional_str);
			break;
		case DISC_ID:
			sprintf(event_str,"DISConnect (user:%s)", aditional_str);
			break;
		case CHAT_ID:
			sprintf(event_str,"CHAT (user:%s) %s", aditional_str, chat_or_query_str);
			break;
		case QUERY_ID:
			sprintf(event_str,"QUERY (user:%s) %s", aditional_str, chat_or_query_str);
			break;
		case QUIT_ID:
			sprintf(event_str,"QUIT (user:%s)", aditional_str);
			break;
		case LOG_ID:
			sprintf(event_str,"LOG (by admin)", aditional_str, chat_or_query_str);
			break;
		case LOG_ID:
			sprintf(event_str,"LOG (by admin)", aditional_str, chat_or_query_str);
			break;
		case START_ID:
			strcpy(event_str, START_STR);
			break;
		case STOP_ID:
			strcpy(event_str, STOP_STR);
			break;
		case RECUP_ID:
			strcpy(event_str, RECUP_STR);
			break;
		default:
			break;
	}
	
	time_str = get_current_time();
	pthread_mutex_lock(&log_mutex);
	log_file = fopen("LOG.txt","a");
	fprintf(log_file,"%s %s",time_str, event_str);
	fclose(log_file);
	pthread_mutex_unlock(&log_mutex);
	
	return 0;
}

void destroy_log(){
	pthread_mutex_destroy(&log_mutex);
	return;
}
