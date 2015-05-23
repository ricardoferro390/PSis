#include "message.h"

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
	
	if(aux->next==NULL){
		aux->next = new_user;
		return 0;
	}
	else{
		aux = aux->next;
		do{
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
		return 0;	//elemento correctamente adicionado
	}
}

int remove_element(user * client){
	user * aux = client_list;
	user * aux_to_remove;
	
	if(aux->next==NULL){
		return 1;
	}
	
	while(aux->next!=NULL){
		if(strcmp(aux->next->username, client->username )==0){
			aux_to_remove = aux->next;
			aux->next=aux->next->next;
			printf("Utilizador %s encontrado...\n", client->username);
			free(aux_to_remove);
			printf("...e removido!\n");
			return 0;
		}
		aux = aux->next;
	}
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

void broadcast(char * arg){
	
	printf("entrei no broadcast\n");
	user * aux = client_list;
	Message msgSent;
	printf("5\n");
	msgSent = create_message(CHAT_ID, arg);				

	while(aux!=NULL){
		if(aux->username!=NULL){
			send_message(aux->sock, msgSent);
			printf("A enviar para: %s\tsocket:%d\n", aux->username, aux->sock);
		}
		aux = aux->next;
	}
}
	

