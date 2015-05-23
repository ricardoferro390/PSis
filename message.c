#include "ProtoBuffers.pb-c.h"
#include "message.h"

void send_message(int sock, Message msg){
	char * buffer;
	
	buffer = malloc(message__get_packed_size(&msg));
	message__pack(&msg, buffer);
	send(sock, buffer, message__get_packed_size(&msg), 0);
	
}

Message * receive_message(int sock){
	char buffer[MAX_SIZE];
	Message * msg;
	
	size_t len = read(sock, buffer, MAX_SIZE);
	if(len==0) return NULL;
	msg = message__unpack(NULL, len, buffer);
	
	return msg;
}

Message create_message(int type, char* string){
	Message msg = MESSAGE__INIT;

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
		default:
			msg.type = INVALID_ID;
			break;
	}
	
	return msg;
}
