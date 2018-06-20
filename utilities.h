#ifndef UTILITIES_H
#define UTILITIES_H
#include <stdlib.h>
	
	void cls();
	
	void mostrar_mapa(int[10][10]);

/*  SLEEP  */
#ifdef _Windows
	#include <windows.h>
	#define sleep( x ) Sleep( (x * 1000) )
#else
	#include <unistd.h>
#endif
	
	void insertList(struct list*, int, int*);
	
	void mostrar_list(struct list);
	
	void liberar_nodo(struct node*);
	
#endif //UTILITIES_H