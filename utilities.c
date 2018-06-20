#include "inicio.h"
#include "utilities.h"
#include <stdlib.h>
#include <stdio.h>

void insertList(struct list* List, int y, int * barco){	
	struct node* temp = malloc(sizeof(struct node));
	temp->y = y;
	temp->barco = barco;
	temp->sig = List->list;
	List->list = temp;
	List->largo++;
}

void cls(){
	fflush(stdout);
	sleep(1.5);
#ifdef WIN32
	system("cls");
#else
	system("clear");
#endif
}

void liberar_nodo(struct node* nodo){
	
}

void mostrar_list(struct list Lista){
	if(Lista.list != NULL){	
		for(struct node* it=Lista.list; it != NULL; it = it->sig){
			printf("%i\t", it->y);
		}
	}
	printf("Null\n");
}

void mostrar_mapa(int mapa[10][10]){
	const char * simbolos[] = {"x", "~", "b", "O", "h"};
	for(int i=0; i<10; i++){
		for(int j=0; j<10; j++)
			printf("%s", simbolos[mapa[i][j]]);
		printf("\n");
	}
	printf("\n");
	fflush(stdout);
}
