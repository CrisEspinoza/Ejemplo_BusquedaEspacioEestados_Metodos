#include "struct.h"
#include "funciones.h"
#include <stdio.h>

//Variables globales

int CONTCERRADOS = 0;
int ORIGEN = 0;
int CONTUNI = 0;

// Funcion que se encarga de inicializar y pedir memoria ecesario para la matriz y sus estructuras que se ocupan

Matriz* iniciarMatriz(int fila, int columna)
{
	Matriz* matriz = (Matriz*)malloc(sizeof(Matriz));
	matriz->fila = fila;
	matriz->columna= columna;
	matriz->casillero = (Casillero**)malloc(sizeof(Casillero*)*fila);
	int i,j;
 	
 	if(!matriz->casillero)
 	{
 		perror("## NO HAY SUFICIENTE MEMORIA PARA LA ASIGNACION ##");
		exit(0);
 	}
	
	for (i = 0; i < fila; i++)
	{
		matriz->casillero[i] = (Casillero*)malloc(sizeof(Casillero)*columna);
 		if(!matriz->casillero[i])
 		{
 			perror("## NO HAY SUFICIENTE MEMORIA PARA LA ASIGNACION ##");
			exit(0);
 		}
	}

	for (i = 0; i < matriz->fila; i++)
	{
		for (j = 0; j < matriz->columna ; j++)
		{
			matriz->casillero[i][j].estado = 1; 
		}
	}

	//mostrarMatriz(matriz);

	return matriz;
}

// Funcion que se encarga de mostrar la matriz 
void mostrarMatriz(Matriz* matriz)
{
	int i,j;

	for (i = 0; i < matriz->fila; i++)
	{
		for (j = 0; j < matriz->columna ; j++)
		{
			printf("%d" ,matriz->casillero[i][j].estado ); 
		}
		printf("\n");
	}

	printf("\n");
	printf("------------- TERMINO LA MUESTRA DE LA MATRIZ ---------------- \n ");
	printf("\n");
}

//Funcion que nos permite liberar la memoria que pedimos para la matriz, así evitamos que se nos sobreescriba.
void liberar(Matriz* matriz)
{
	int i;
	for (i = 0; i < matriz->fila; i++)
	{
		free(matriz->casillero[i]);
	}
	free(matriz->casillero);
	free(matriz);
}


//Funcion que genera de forma random, las paredes en la matriz, en las cuales se van a ver reflejados las paredes
void randMatriz(Matriz* matriz, int cantidad, int uso)
{
    srand(time(NULL));
    int limiteMayorFila = matriz->fila, limiteMayorColumna = matriz->columna;
    int randFila,randColumna,i; 

    if (uso == 1)
    {
		for (i = 0; i < cantidad ; i++)
		{
			do // Parte del codigo que nos sirve para evitar que se nos repitan los numeros y coloquemos paredes en posiciones correctas
			{
				randFila = rand()%limiteMayorFila;
				randColumna = rand()%limiteMayorColumna;
				//printf("%d\n", matriz->casillero[randFila][randColumna].estado);
			}while(matriz->casillero[randFila][randColumna].estado != 1);
	    	
	    	//printf("Numero Fila es : %d -", randFila);
	    	//printf("Numero Columna es : %d \n", randColumna);
	    	matriz->casillero[randFila][randColumna].estado = 2;
		}
	}

	if (uso == 2)
	{		
		for (i = 0; i < cantidad ; i++)
		{
			do // Parte del codigo que nos sirve para evitar que se nos repitan los numeros y coloquemos habitaciones limpias en posiciones correctas
			{
				randFila = rand()%limiteMayorFila;
				randColumna = rand()%limiteMayorColumna;
				//printf("%d\n", matriz->casillero[randFila][randColumna].estado);
			}while(matriz->casillero[randFila][randColumna].estado != 1);
	    	
	    	//printf("Numero Fila es : %d -", randFila);
	    	//printf("Numero Columna es : %d \n", randColumna);
	    	matriz->casillero[randFila][randColumna].estado = 3;
		}
	}
}

// FUncion que verifica si tenemos toda la matriz, es decir, los departmentos limpios
int revisarMatriz (Matriz* matriz)
{
	int i,j;

	for (i = 0; i < matriz->fila; i++)
	{
		for (j = 0; j < matriz->columna; j++)
		{
			if (matriz->casillero[i][j].estado == 1)
				return 0;
		}
	}

	return 1;
}

void realizarLimpieza(Matriz* matriz)
{
	Posicion* listaPendientes;
	Posicion* listaCerrados;
	Posicion* listaActual;

	// Realizamos las transciones posibles 
	Posicion listaTranciones[4];
	// Arriba
	listaTranciones[0].fila = 1;
	listaTranciones[0].columna = 0;
	// Abajo
	listaTranciones[1].fila = -1;
	listaTranciones[1].columna = 0;
	// Derecha
	listaTranciones[2].fila = 0;
	listaTranciones[2].columna = 1;
	// Izquierda
	listaTranciones[3].fila = 0;
	listaTranciones[3].columna = -1;

	listaActual = (Posicion*)malloc(sizeof(Posicion) * (matriz->fila * matriz->columna) );
	listaCerrados = (Posicion*)malloc(sizeof(Posicion) * (matriz->fila * matriz->columna) );
	listaPendientes = (Posicion*)malloc(sizeof(Posicion) * (matriz->fila * matriz->columna) );

	int i;

	srand(time(NULL));
    int limiteMayorFila = matriz->fila, limiteMayorColumna = matriz->columna;
    int randFilaComienzo,randColumnaComienzo; 

	do // Parte del codigo que nos sirve para evitar que se nos repitan los numeros y coloquemos habitaciones limpias en posiciones correctas
	{
		randFilaComienzo = rand()%limiteMayorFila;
		randColumnaComienzo = rand()%limiteMayorColumna;
		//printf("%d\n", matriz->casillero[randFilaComienzo][randColumnaComienzo].estado);
	}while(matriz->casillero[randFilaComienzo][randColumnaComienzo].estado != 1);

	listaActual[ORIGEN].fila = randFilaComienzo;
	listaActual[ORIGEN].columna = randColumnaComienzo;
	listaActual[ORIGEN].origen = ORIGEN;
	
	//printf("Las posiciones de inicio son: %d - %d \n", randFilaComienzo,randColumnaComienzo);

	do // Parte del codigo que nos sirve para evitar que se nos repitan los numeros y coloquemos habitaciones limpias en posiciones correctas
	{
		for (i = 0; i < 4; i++)
		{
			if ( (listaActual[ORIGEN].fila + listaTranciones[i].fila ) >= 0 && (listaActual[ORIGEN].columna + listaTranciones[i].columna ) >= 0 ) // Verificamos que las posiciones nuevas sean mayores a 0
			{
				printf("Primero paso pasado \n");

				if ( (listaActual[ORIGEN].fila + listaTranciones[i].fila) < matriz->fila && (listaActual[ORIGEN].columna + listaTranciones[i].columna) < matriz->columna ) // Verificamos que esten dentro del rango de la matriz
				{
					printf("Segundo paso pasado\n");

					if ( matriz->casillero[(listaActual[ORIGEN].fila + listaTranciones[i].fila)][(listaActual[ORIGEN].columna + listaTranciones[i].columna)].estado != 3 ) // Verificamos que no sea una pared, para poder avanzar
					{
						printf("Tercer paso pasado\n");

						if( estadosPendientes(listaPendientes, (listaActual[ORIGEN].fila + listaTranciones[i].fila) , (listaActual[ORIGEN].columna + listaTranciones[i].columna)) == 1 )  // Revisamos si ya esta en la lista de pendientes
						{
							printf("CUARTO PASO ----------------------- *********************** ******************** \n");
							listaPendientes[CONTUNI].fila = (listaActual[ORIGEN].fila + listaTranciones[i].fila);
                        	listaPendientes[CONTUNI].columna = (listaActual[ORIGEN].columna + listaTranciones[i].columna); 
                        	listaPendientes[CONTUNI].origen = ORIGEN;
                        	CONTUNI++;
						}

					}
				}
			}   
		}

		// Aca declaramos el nuevo estado cerrado
	    listaCerrados[CONTCERRADOS].fila = listaActual[ORIGEN].fila;
	    listaCerrados[CONTCERRADOS].columna = listaActual[ORIGEN].columna;


	    // Revisamos si tiene que limpiar o no el departamento.
	    if (matriz->casillero[listaActual[ORIGEN].fila][listaActual[ORIGEN].columna].estado == 1)
	    {
	    	matriz->casillero[listaActual[ORIGEN].fila][listaActual[ORIGEN].columna].estado = 2;
	    }

	    ORIGEN++;
	    // Cambiamo el estado estado actual y colocamos el origen desde donde proviene, ademas de aumentar el origen para que cada estado actual tena un origen distinto.
	    listaActual[ORIGEN].fila = listaPendientes[CONTCERRADOS].fila;
	    listaActual[ORIGEN].columna = listaPendientes[CONTCERRADOS].columna;
	    listaActual[ORIGEN].origen = ORIGEN;


	    // Aumentamos el contador de estados cerrados para asi no sobreescribir ninguno
	    CONTCERRADOS++;

	}while(revisarMatriz(matriz) != 1); // Revisamos si nuestra matriz (departamentos), ya estan completamente limpios

}

int estadosPendientes (Posicion* listaPendientes, int fila , int columna )
{
	int i;
	for (i = 0; i < CONTUNI; i++)
    {
    	printf("El numero de la i es : %d  y CONTUNI ES : %d \n", i , CONTUNI);
        if (listaPendientes[i].columna == columna && listaPendientes[i].fila == fila) //En caso qe estas sean iguales
        {
            return 0; // Retornamos un 0, verificando que si se encuentra dentro del arreglos de estados cerrados
        }
    }

    return 1;
}
