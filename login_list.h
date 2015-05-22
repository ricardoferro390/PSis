#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum { false, true } bool;
typedef struct _list user;

#define MAX_USERNAME_SIZE 40

struct _list {
	char username[MAX_USERNAME_SIZE];
	int sock;
	user * next;
};

user * create_list();
bool search_element(user* begin, char* username);
bool add_element(user *begin, char *username);
user* remove_element(user* begin, char* username);
void delete_list(user *begin);
void print_list(user* begin);
