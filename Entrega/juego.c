#include "juego.h"
#include "inicio.h"
#include "utilities.h"
#include <stdbool.h>
#include <stdio.h>
#define blanco 3
#define agua 1
#define hundido 4
#define vacio 0

bool juego(struct list* oponente, int anotador[10][10], int mapa[10][10], int tablero_op[10][10])
{
	int x, y;
	while(1){
		printf("Anotador:\n");
		mostrar_mapa(anotador);
	
		printf("Mapa tactico:\n");
		mostrar_mapa(mapa);
		
		printf("Ingrese coordenadas de disparo:\n");
		
		fflush(stdin);
		scanf("%i%i%*c", &x, &y);
		
		if(x < 0 || x > 9 || y < 0 || y > 9)
			printf("Coordenadas invalidas. Intente de nuevo\n");
		else if(anotador[x][y] != vacio)
			printf("Ya ha disparado a esa posicion. Intente de nuevo\n");
		else
			break;
		
		fflush(stdout);
		sleep(2);
		cls();
	}
	
	printf("\nEl disparo fue");
	
	for(int i=0; i<3; i++){
		printf(".");
		fflush(stdout);
		sleep(1);
	}
	printf(" ");
	
	bool b_agua = true;
	if(oponente[x].largo == 0){
		printf("Agua");
		anotador[x][y] = agua;
	}
	else{
		struct node * anterior = NULL;
		for(struct node * aux = oponente[x].list; aux != NULL; anterior = aux, aux = aux->sig){
			if(aux->y == y){
				printf("Blanco");
				
				(*aux->barco)--;
				if(*aux->barco == 0){
					fflush(stdout);
					sleep(1);
					printf("\nHa hundido un barco del rival");
					
					free(aux->barco);
					/* aux->barco = NULL; no es necesario ya que mas adelante
					se libera el nodo completo*/
				}
				
				
				oponente[x].largo--;
				if(anterior != NULL)
					anterior->sig = aux->sig;
				else
					oponente[x].list = aux->sig;
				free(aux);
				
				anotador[x][y] = blanco;
				tablero_op[x][y] = hundido;
				b_agua = false;
				break;
			}
		}
		
		if(b_agua){
			printf("Agua");
			anotador[x][y] = agua;
		}
	}
	
	if(!b_agua){
		bool bandera=true;
		for(int i=0; i<10; i++)
			if(oponente[x].largo != 0){
				bandera = false;
				break;
			}
			
		if(bandera)
			return false;
	}
	
	fflush(stdout);
	sleep(2);
	cls();
	
	return true;
}

void terminar(struct list* jugadores[2]){
	/* Funcion para liberar la memoria alocada
	durante la ejecucion del programa liberando el 
	main de codigo trivial */
	
	for(int n=0; n<2; n++){
		for(int i=0; i<10; i++){
			if(jugadores[n][i].largo != 0){
				struct node* siguiente = NULL;
				for(struct node* aux = jugadores[n][i].list; aux!=NULL; aux=siguiente){
					siguiente = aux->sig;
					free(aux->barco);
					free(aux);
				}	
			}
		}
		free(jugadores[n]);
		jugadores[n] = NULL;
	}
}