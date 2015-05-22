
#include "login_list.h"


user * create_list(){	
	user *begin = malloc(sizeof(user));
	if (begin == NULL){ 
		printf("Nao foi possivel criar lista\n"); 
		//exit(1);
	}
	begin->username = NULL;
	begin->next = NULL;	//proximo elemento aponto para NULL(fim da lista)
	return begin;		//retorna ponteiro para inicio da lista
}

bool search_element(user* begin, char* username){
	while(begin->next!=NULL){
		if(strncmp(begin->username,username,MAX_USERNAME_SIZE)==0){
			return true;	//elemento ja existente na lista
		}	
		begin=begin->next;
	}
	return false;	//elemento nao encontrado
}

int add_element(user *begin, user * new_user, char * username){
	//user * new;	 //create new pointer to list
	
	if(strlen(username)>=MAX_USERNAME_SIZE){
		printf("Grande demais!");
		return 1;
	}
	/*if(search_element(begin, username)){
		//elemento ja esta na lista
		printf("Elemento ja se encontra na lista\n");
		return false; //nao foi possivel adicionar elemento na lista
	}else{*/
		//elemento nao esta na lista, adicionar
			//adiciona elemento ao final da lista
		while(begin->next!=NULL){		
			begin=begin->next;
		}
		strncpy(new_user->username, username, MAX_USERNAME_SIZE);
		begin->next = new_user;		
		new_user->next = NULL;
		
			
		return 0;	//elemento correctamente adicionado
	//}
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
	

