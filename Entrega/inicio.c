#include "inicio.h"
#include "utilities.h"
#include "juego.h"
#include <stdio.h>
#include <stdbool.h>
#define barco 2
#define agua 1
#define vacio 0
#define legal(x) (x>=0 && x<10)

int max(int x, int y){
	if(x > y) return x;
	else return y;
}

int min(int x, int y){
	if(x < y) return x;
	else return y;
}
			
bool alrededores(int tablero[10][10], int x, int y){
	for(int i=-1; i<2; i++){
		for(int j=-1; j<2; j++){
			if(legal(x-i) && legal(y-j) &&
				tablero[x-i][y-j] == barco)
				return true;
		}
	}
	return false;
}

void init(struct list** jugador1,
			struct list** jugador2,
			int tableros[2][10][10],
			int anotadores[2][10][10])
{
	(*jugador1) = malloc(sizeof(struct list)*10);
	(*jugador2) = malloc(sizeof(struct list)*10);
	
	for(int i=0; i<10; i++){
		(*jugador1)[i].list = (*jugador2)[i].list = NULL;
		(*jugador1)[i].largo = (*jugador2)[i].largo = 0;
	}
	
	for(int j=0; j<10; j++){
		for(int k=0; k<10; k++){
			tableros[0][j][k] = \
			tableros[1][j][k] = agua;
			anotadores[0][j][k] = \
			anotadores[1][j][k] = vacio;
		}
	}
	
}

void construir(struct list** jugadores, int tableros[2][10][10])
{
	/*
	Se predefinen para la cantidad de barcos y el tamaño:
	1 submarino
	2 destructores
	3 cruceros
	1 acorazado
	*/
	
	int jugador = 0;
	
	do{		
		int cantidades[] = {0, 1, 0, 0};
		const char* barcos[] = {"Submarino", "Destructor",
								"Crucero", "Acorazado"};
		nuevo_barco:{
		cls();
		
		printf("\tJugador actual: Jugador%i\n", jugador);
		printf("Barcos restantes:\n");
		
		for(int i=0; i<4; i++)
			printf("%i\t%s[%i]\n", i, barcos[i], cantidades[i]);
		
		int entrada;
		confirm_input:{

		printf("\nIngrese un indice(0-3) para seleccionar un barco:\n");
		scanf("%i%*c", &entrada);
		
		if(entrada < 0 || entrada > 3){
			printf("Indice erroneo. Vuelva a intentar");
			goto confirm_input;
		}
		if(cantidades[entrada] == 0){
			printf("Cantidad del barco \"%s\" es 0. Vuelva a intentar", barcos[entrada]);
			goto confirm_input;
		}
		}
		
		{//else
		int x1, x2, y1, y2;
			
		insert_barco:{
		cls();
		
		printf("Mapa tactico:\n");
		mostrar_mapa(tableros[jugador]);
		
		printf("\tBarco seleccionado: %s (largo = %i)\n\n", barcos[entrada], entrada+1);
		
		do{
			//incluir mensaje de error
			printf("Ingrese un valor x e y inicial:\n");
			scanf("%i%i%*c", &x1, &y1);
		}while(x1 < 0 || x1 >= 10 ||
				y1 < 0 || y1 >= 10);
					
		do{
			//incluir mensaje de error
			printf("Ingrese un valor x e y final:\n");
			scanf("%i%i%*c", &x2, &y2);
		}while(x2 < 0 || x2 >= 10 ||
				y2 < 0 || y2 >= 10);
					
		int dist_x = abs(x2-x1);
		int dist_y = abs(y2-y1);
			
		//entrada+1 = largo barco
		bool entrada_valida = (
		(dist_x == 0 && dist_y == entrada+1) ||
		(dist_y == 0 && dist_x == entrada+1));
		//barcos validos: horizontales y verticales
			
		if(!entrada_valida){
			printf("Forma del barco erronea. Vuelva a intentar");
			fflush(stdout);
			sleep(2);
			
			goto insert_barco;
		}
			
		//analizar los alrededores de (x1,y1)-(x2,y2)
		if(dist_x == 0){
			for(int i=min(y1, y2); i < max(y1, y2); i++){
				if(alrededores(tableros[jugador], x1, i)){
					printf("El rango seleccionado coincide con los alrededores o \ncon una "
					"casilla de otro barco. Vuelva a intentar");
					fflush(stdout);
					sleep(2);
					
					goto insert_barco;
				}
			}
			
			//dibujar barco
			int * aux = malloc(sizeof(int)); *aux = entrada+1;
			for(int i=min(y1, y2); i < max(y1, y2); i++){
				tableros[jugador][x1][i] = barco;
				
				insertList(&jugadores[jugador][x1], i, aux);
			}
		} else { // dist_y = 0
			for(int i=min(x1, x2); i<max(x1, x2); i++){
				if(alrededores(tableros[jugador], i, y1)){
					printf("El rango seleccionado coincide con los alrededores o \ncon una "
					"casilla de otro barco. Vuelva a intentar");
					fflush(stdout);
					sleep(2);
					
					goto insert_barco;
				}
			}
				
			//dibujar barco
			int * aux = malloc(sizeof(int)); *aux = entrada+1;
			for(int i=min(x1, x2); i < max(x1, x2); i++){
				tableros[jugador][i][y1] = barco;
				
				insertList(&jugadores[jugador][i], y1, aux);
			}
		}
		}
		
		cantidades[entrada]--;
		}
		
		for(int i=0; i<4; i++){
			if(cantidades[i] != 0)
				goto nuevo_barco;
		}
		}
		jugador++;
	}while(jugador < 2);
	
}