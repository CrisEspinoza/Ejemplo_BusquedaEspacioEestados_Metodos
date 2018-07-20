# include <stdlib.h>

#ifndef _STRUCTS_H_
#define _STRUCTS_H_

typedef struct Posicion
{
	int fila;
	int columna;
	int origen;
} Posicion;

typedef struct Casillero
{
	int estado;
	Posicion posicion;
} Casillero;

typedef struct Matriz
{
	int fila;
	int columna;
	Casillero** casillero;
} Matriz;

#endif