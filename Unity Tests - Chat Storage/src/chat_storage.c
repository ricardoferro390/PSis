#include "chat_storage.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int number_of_messages;
cs * cs_list;

void cs_init(){	
	cs_list = malloc(sizeof(cs));
	if (cs_list == NULL){ 
		printf("Nao foi possivel criar lista\n"); 
	}
	cs_list->message = NULL;
	cs_list->id = 0;
	cs_list->next = NULL;
	number_of_messages = 0;
	return;
}

cs* create_message(char * message){
	cs * new;
	
	new = malloc(sizeof(cs));
	
	new->message = malloc(MAX_MESSAGE_SIZE*sizeof(char));
	strcpy(new->message, message);
	new->id=number_of_messages+1;
	new->next=NULL;
	
	number_of_messages++;
	
	return new;
}

void add_message(char * message){
	cs * new_message; 
	cs * aux = cs_list;
	
	if(strlen(message)>=MAX_MESSAGE_SIZE){
		printf("Mensagem grande demais\n");
		return;
	}
	
	new_message = create_message(message);
	
	if(aux->next==NULL){
		aux->next = new_message;
		return;
	}else{
		aux = aux->next;
		do{
			if(aux->next==NULL){
				aux->next = new_message;
				return;
			}
			aux = aux->next;
		}while(aux!=NULL);	
		return;
	}
}

int query(int a, int b){
	cs * aux = cs_list;
	
	if(a>number_of_messages){
		printf("Nao existem mensagens a comecar com este id_min\n");
		return 0;
	}else{
		//procura um intervalo de mensagens
		while(aux!=NULL){
			if(aux->id==a){
				break;
			}
			aux=aux->next;
		}
		while(aux!=NULL){
			if(aux->id<=b){
				printf("Message %d: %s\n",aux->id, aux->message);
			}else{
				break;
			}
			aux=aux->next;
		}
		return 1;
	}
}

