#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef enum { false, true } bool;
typedef struct _list user;

#define MAX_USERNAME_SIZE 40

struct _list {
	char * username;
	pthread_t thread_id;
	int sock;
	user * next;
};

void create_list();
int search_element(user* begin, char* username);
int add_element(user * new_user);
user* remove_element(user* begin, char* username);
void delete_list(user *begin);
void print_list(user* begin);
user * create_user(int sock);
