/*login_list.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login_list.h"

list * create_list(){	
	list *begin;
			
	begin = malloc(sizeof(list));
	if (begin == NULL){ 
		printf("Nao foi possivel criar lista\n"); 
		//exit(1);
	}
	begin->next=NULL;	//proximo elemento aponto para NULL(fim da lista)
	
	return begin;		//retorna ponteiro para inicio da lista
}

bool search_element(list* begin, char* username){
	while(begin->next!=NULL){
		if(strncmp(begin->username,username,20)==0){
			return true;	//elemento ja existente na lista
		}	
		begin=begin->next;
	}
	return false;	//elemento nao encontrado
}

bool add_element(list *begin, char *username){
	list * new;	 //create new pointer to list

	if(search_element(begin, username)){
		//elemento ja esta na lista
		printf("Elemento ja se encontra na lista\n");
		return false; //nao foi possivel adicionar elemento na lista
	}else{
		//elemento nao esta na lista, adicionar
		new = malloc(sizeof(list));
		if(new==NULL){
			printf("Nao foi possivel criar elemento!");
			return false;
		}else{
			//adiciona elemento ao final da lista
			while(begin->next!=NULL){		
				begin=begin->next;
			}
			begin->next=new;		
			new->next=NULL;
			strncpy(new->username,username,20);
			
			return true;	//elemento correctamente adicionado
		}
	}
}

list* remove_element(list* begin, char* username){
	
	list * aux;
	list * ant;
		
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
		if(strncmp(aux->username,username,20)==0){
			ant->next=aux->next;
			free(aux);
			return begin;
		}else{
			ant=aux;
			aux=aux->next;
		}	
	}
	
	//verificar se e o ultimo elemento da lista
	if(strncmp(aux->username,username,20)==0){
		ant->next=aux->next;
		free(aux);
		return begin;
	}
	
	//elemento nao foi encontrado
	return begin;
}

void delete_list(list *begin){

	list * aux;
	list * aux2;

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

void print_list(list* begin){
	list * aux;
	
	aux=begin->next;
	while(aux!=NULL){		
		printf("%s\n",aux->username);	
		aux=aux->next;		
	}

	return;
}
	


int main(int argc, char **argv)
{
	
	list* begin;
	begin=create_list();
	
	char* str1 = "ferro";
	//char* str2 = "diogo";
	//char* str3 = "jnos";
	//char* str4 = "cenas";
	
	char* str5 = "abcdefghijklmnopqrst";
	char* str6 = "abcdefghijklmnopqrstuvx";
	
	printf("%d\n",strlen(str5));
	printf("%d\n",strlen(str6));
	
	add_element(begin, str1);
	//add_element(begin, str2);
	//add_element(begin, str3);
	//add_element(begin, str4);
	add_element(begin, str5);
	add_element(begin, str6);
	
	print_list(begin);
	
	
	return 0;
}

