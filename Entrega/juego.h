#ifndef JUEGO_H
#define JUEGO_H
#include <stdbool.h>
#include "inicio.h"
	
	bool juego(struct list *, int[10][10],
		int[10][10], int[10][10]);
	
	void terminar(struct list * aux[]);
	
#endif