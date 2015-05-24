#include "ProtoBuffers.pb-c.h"
#include "message.h"

void send_to_fifo(int fifo_fd, Message msg){
	char * buffer;
	
	buffer = malloc(message__get_packed_size(&msg));
	message__pack(&msg, buffer);
	if(write(fifo_fd, buffer, message__get_packed_size(&msg))==-1)
		perror("write");
}

Message * receive_from_fifo(int fifo_fd){
	char buffer[sizeof(Message)];
	Message * msg;
	
	size_t len = read(fifo_fd, buffer, sizeof(buffer));
	if(len==0) return NULL;
	msg = message__unpack(NULL, len, buffer);
	
	return msg;
}


void send_message(int sock, Message msg){
	char * buffer;
	
	buffer = malloc(message__get_packed_size(&msg));
	message__pack(&msg, buffer);
	if(send(sock, buffer, message__get_packed_size(&msg), 0)==-1)
		perror("send");
}

Message * receive_message(int sock){
	char buffer[MAX_SIZE];
	Message * msg;
	
	size_t len = read(sock, buffer, sizeof(buffer));
	if(len==0) return NULL;
	msg = message__unpack(NULL, len, buffer);
	
	return msg;
}

Message create_message(int type, char* string){
	Message msg = MESSAGE__INIT;
	int cmd_int_arg1, cmd_int_arg2;
	
	switch(type){
		case LOGIN_ID:
			msg.type = LOGIN_ID;
			msg.username = strdup(string);
			break;
		case DISC_ID:
			msg.type = DISC_ID;
			break;
		case CHAT_ID:
			msg.type = CHAT_ID;
			msg.chat = strdup(string);
			break;
		case QUERY_ID:
			msg.type = QUERY_ID;
			sscanf(string, "%*s %d %d", &cmd_int_arg1, &cmd_int_arg2);
			msg.query_id_min = cmd_int_arg1;
			msg.has_query_id_min = 1;
			msg.query_id_max = cmd_int_arg2;
			msg.has_query_id_max = 1;
			break;
		case OK_ID:
			msg.type = OK_ID;
			break;
		case QUIT_ID:
			msg.type = QUIT_ID;
			break;
		case LOG_ID:
			msg.type = LOG_ID;
			break;
		case LOG_RESP_ID:
			msg.type = LOG_RESP_ID;
			msg.log_resp = string;
			break;
		default:
			msg.type = INVALID_ID;
			break;
	}
	
	return msg;
}
