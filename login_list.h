#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum { false, true } bool;
typedef struct _list list;

#define MAX_USERNAME_SIZE 40

struct _list {
	char username[MAX_USERNAME_SIZE];
	list * next;
};

list * create_list();
bool search_element(list* begin, char* username);
bool add_element(list *begin, char *username);
list* remove_element(list* begin, char* username);
void delete_list(list *begin);
void print_list(list* begin);
