
#include "login_list.h"

user * client_list;

void create_list(){	
	client_list = malloc(sizeof(user));
	if (client_list == NULL){ 
		printf("Nao foi possivel criar lista\n"); 
		//exit(1);
	}
	client_list->username = NULL;
	client_list->next = NULL;	//proximo elemento aponto para NULL(fim da lista)
}

int search_element(user* begin, char* username){
	printf("cheguei aqui!");
	
	if(strcmp(begin->username,username)==0) return 1;
	while(begin->next!=NULL){
		if(strcmp(begin->username,username)==0)	return 1;	//elemento ja existente na lista
		begin = begin->next;
	}
	return 0;	//elemento nao encontrado
}

int add_element(user * new_user){
	user * aux = client_list;
	
	if(strlen(new_user->username)>=MAX_USERNAME_SIZE){
		printf("Grande demais!");
		return 1;
	}
	printf("Cheguei ao 1\n");
	
	
	if(aux->next==NULL){
		aux->next = new_user;
		return 0;
	}
	else{
		printf("Cheguei ao 4\n");
		aux = aux->next;
		do{
			printf("Cheguei ao 5\n");	
			printf("lista->username=%s\nnew_user->username=%s\n", aux->username, new_user->username);
			if(strcmp(aux->username, new_user->username)==0){
				printf("username já utilizado!\n");
				return 1;
			}
			if(aux->next==NULL){
				aux->next = new_user;
				return 0;
			}
			aux = aux->next;
		}while(aux!=NULL);	
		
		printf("Cheguei ao 7\n");
		return 0;	//elemento correctamente adicionado
	}
}

user* remove_element(user* begin, char* username){
	
	user * aux;
	user * ant;
		
	aux=begin->next;
	ant=begin->next;
	
	if(aux==NULL){
		//lista sem elementos
		return begin;
	}
	
	//verificar se e o primeiro elemento da lista
	if(strncmp(aux->username,username,20)==0){				
		begin->next=aux->next;
		free(aux);	
		return begin;
	}

	//verificar elementos no meio da lista (excepto o ultimo)
	while(aux->next!=NULL){
		if(strncmp(aux->username,username,MAX_USERNAME_SIZE)==0){
			ant->next=aux->next;
			free(aux);
			return begin;
		}else{
			ant=aux;
			aux=aux->next;
		}	
	}
	
	//verificar se e o ultimo elemento da lista
	if(strncmp(aux->username,username,MAX_USERNAME_SIZE)==0){
		ant->next=aux->next;
		free(aux);
		return begin;
	}
	
	//elemento nao foi encontrado
	return begin;
}

void delete_list(user *begin){

	user * aux;
	user * aux2;

	//se a lista esta vazia, eliminar o ponteiro inicial
	if(begin->next==NULL){
		free(begin);
	}else{
		//eliminar todos os restantes elementos
		aux=begin->next;
		while(aux->next!=NULL){
			aux2=aux->next;
			free(aux);
			aux=aux2;
		}		
		free(aux);		
	}
	
	return;
}

void print_list(user* begin){
	user * aux;
	
	aux=begin->next;
	while(aux!=NULL){		
		printf("%s\n",aux->username);	
		aux=aux->next;		
	}

	return;
}

user * create_user(int sock){

	user * new_user = (user*)malloc(sizeof(user));
	new_user->username = NULL;
	new_user->next = NULL;
	new_user->sock = sock;
	return new_user;

}
	

