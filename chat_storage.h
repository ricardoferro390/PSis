#ifndef chat_storage_H
#define chat_storage_H

typedef struct _cs cs;

#define MAX_MESSAGE_SIZE 1024

struct _cs {
	int id;
	char * message;
	cs * next;
};

void cs_init();
cs* create_chat(char * message);
void add_message(char * message);
char * query(int a, int b);
#endif // chat_storage_H
