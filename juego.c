#include "juego.h"
#include "inicio.h"
#include "utilities.h"
#include <stdbool.h>
#include <stdio.h>
#define blanco 3
#define agua 1
#define hundido 4

bool juego(struct list* oponente, int anotador[10][10], int mapa[10][10], int tablero_op[10][10])
{
	printf("Anotador:\n");
	mostrar_mapa(anotador);
	
	printf("Mapa tactico:\n");
	mostrar_mapa(mapa);
	
	int x, y;
	validate_input:{
	printf("Ingrese coordenadas de disparo:\n");
	
	scanf("%i%i%*c", &x, &y);
	
	if(x < 0 || x > 9 || y < 0 || y > 9){
		printf("Coordenadas invalidas. Intente de nuevo\n");
		
		goto validate_input;
	}
	}
	
	printf("\n");
	bool bandera = true;
	if(oponente[x].largo == 0){
		printf("Agua");
		anotador[x][y] = agua;
	}
	else{
		struct node * anterior = NULL;
		for(struct node * aux = oponente[x].list; aux != NULL; anterior = aux, aux = aux->sig){
			if(aux->y == y){
				printf("Blanco");
				/*
				*(aux->barco)--;
				if(*(aux->barco) == 0){
					//free(temp);
					printf("\nHundido");
				}
				*/
				oponente[x].largo--;
				if(anterior != NULL)
					anterior->sig = aux->sig;
				else
					oponente[x].list = aux->sig;
				fflush(stdout);
				free(aux);
				
				anotador[x][y] = blanco;
				tablero_op[x][y] = hundido;
				bandera = false;
				break;
			}
		}
		
		if(bandera){
			printf("Agua");
			anotador[x][y] = agua;
		}
	}
	
	fflush(stdout);
	sleep(2);
	cls();
	
	if(!bandera){
		bool bandera2=true;
		for(int i=0; i<10; i++)
			if(oponente[x].largo != 0){
				bandera2 = false;
				break;
			}
			
		if(bandera2)
			return false;
	}
	return true;
}