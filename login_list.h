
typedef struct _list user;

#define MAX_USERNAME_SIZE 40

struct _list {
	char * username;
	pthread_t thread_id;
	int sock;
	user * next;
};

void create_list();
int add_element(user * new_user);
int remove_element(user * client);
void delete_list(user *begin);
void print_list(user* begin);
user * create_user(int sock);
void broadcast(char * arg);
