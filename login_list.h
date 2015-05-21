
typedef enum { false, true } bool;
typedef struct _list list;

struct _list {
	char username[21];
	list * next;
};

list * create_list();
bool search_element(list* begin, char* username);
bool add_element(list *begin, char *username);
list* remove_element(list* begin, char* username);
void delete_list(list *begin);
void print_list(list* begin);
