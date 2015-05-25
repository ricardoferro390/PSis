typedef struct _cs cs;

#define MAX_MESSAGE_SIZE 1024

struct _cs {
	int id;
	char * message;
	cs * next;
};

void cs_init();
cs* create_message(char * message);
void add_message(char * message);
int query(int a, int b);
