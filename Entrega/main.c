#include <stdbool.h>
#include <stdio.h>
#include "juego.h"
#include "inicio.h"
#include "utilities.h"

int main(){
	struct list * jugadores[2];
	int tableros[2][10][10], anotadores[2][10][10];
	
	init(&jugadores[0], &jugadores[1], tableros, anotadores);
	
	construir(jugadores, tableros);
	
	cls();
	bool bandera = true;
	bool turno = true;
	do{
		printf("Jugador %d, es su turno. ", turno);
		printf("Presione enter para continuar...");
		fflush(stdin);
		getchar();
		
		cls();
		
		bandera = juego(jugadores[!turno], anotadores[turno],
					tableros[turno], tableros[!turno]);
		turno = !turno;
	}while(bandera);
	
	fflush(stdout);
	sleep(1.5);
	printf("\n\nHA GANADO EL JUGADOR %i.. Felicitaciones\n", turno);
	
	terminar(jugadores);
	
	return 0;
}