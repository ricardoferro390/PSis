#include "chat_storage.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_SIZE 2000000

int number_of_messages;
cs * cs_list;
pthread_mutex_t chat_mutex;

void cs_init(){	
	pthread_mutex_init(&chat_mutex, NULL);
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

cs* create_chat(char * message){
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
	pthread_mutex_lock(&chat_mutex);
	if(strlen(message)>=MAX_MESSAGE_SIZE){
		printf("Mensagem grande demais\n");
		pthread_mutex_unlock(&chat_mutex);
		return;
	}
	
	new_message = create_chat(message);
	
	if(aux->next==NULL){
		aux->next = new_message;
		pthread_mutex_unlock(&chat_mutex);
		return;
	}else{
		aux = aux->next;
		do{
			if(aux->next==NULL){
				aux->next = new_message;
				pthread_mutex_unlock(&chat_mutex);
				return;
			}
			aux = aux->next;
		}while(aux!=NULL);	
		pthread_mutex_unlock(&chat_mutex);
		return;
	}
}

char * query(int a, int b){
	cs * aux = cs_list;
	char * buffer = malloc(MAX_SIZE);
	char * buffer_final = malloc(MAX_SIZE);
	pthread_mutex_lock(&chat_mutex);
	if(a>number_of_messages){
		printf("Nao existem mensagens a comecar com este id_min\n");
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
				sprintf(buffer, "%d: %s\n",aux->id, aux->message);
				strcat(buffer_final, buffer);
				//printf("Message %d: %s\n",aux->id, aux->message);
			}else{
				break;
			}
			aux=aux->next;
		}

	}
	pthread_mutex_unlock(&chat_mutex);
	return buffer_final;
}

