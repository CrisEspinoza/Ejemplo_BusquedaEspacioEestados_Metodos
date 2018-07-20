# include <stdlib.h>

# ifndef _FUNCIONES_H_
# define _FUNCIONES_H_

#include "struct.h"

// Estas son las cabeceras de las funciones que se ocupan dentro del programa

Matriz* iniciarMatriz(int fila, int columna);
void mostrarMatriz(Matriz* matriz);
void liberar(Matriz* matriz);
void randMatriz(Matriz* matriz,int cantidad, int uso);
void realizarLimpieza(Matriz* matriz);
int estadosPendientes (Posicion* listaPendientes, int fila , int columna );

#endif