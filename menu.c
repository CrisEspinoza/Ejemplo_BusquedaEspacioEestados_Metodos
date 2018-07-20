#include <stdio.h>

#include "funciones.c"

// EL menu de la aplicación que se le muestra al usuario para que realice las funcionalidades del laboratorio

void menu()
{
    int filas,columnas,opcion,bandera=0;
    Matriz* matriz = (Matriz*)malloc(sizeof(Matriz));

    do
    {
        printf( "\n   1. Comenzar problema");
        printf( "\n   2. Reiniciar programa");
        printf( "\n   3. Creditos" );
        printf( "\n   4. Salir" );
        printf( "\n\n   Introduzca opcion (1-4): ");

        scanf( "%d", &opcion );

        /* Inicio del anidamiento */

        switch ( opcion )
        {
            case 1: if (bandera != 0)
                    {
                        printf("Ya creo la matriz, debe reiniciar el programa !! \n");
                        break;
                    }
                    // Pedimos la cantidad de filas y columnas para crear la matriz
                    printf("Ingrese cantidad de filas\n");
                    scanf("%d",&filas);
                    printf("Ingrese cantidad de columnas\n");
                    scanf("%d",&columnas);
                    printf("Usted ingreso %d filas y %d columnas\n", filas,columnas);
                    matriz = iniciarMatriz(filas,columnas);
                    randMatriz(matriz,2,1); //Primero colocamos las paredes
                    printf("aca1\n");
                    randMatriz(matriz,2,2); //Luego colocamos las habitaciones que ya estan limpias                    
                    printf("aca\n");
                    mostrarMatriz(matriz);
                    printf("********************* -------------------------- MATRIZ PRIMARIA ------------------------------- ********************\n");
                    printf("\n");
                    printf("aca2\n");
                    realizarLimpieza(matriz);
                    printf("aca3\n");
                    mostrarMatriz(matriz);
                    // system("clear");
                    printf("aca4\n");
                    bandera++;
                    break;

            case 2: //Liberando la memoria
                    liberar(matriz);
                    bandera = 0;
                    CONTCERRADOS = 0;
                    ORIGEN = 0;
                    CONTUNI = 0;
                    break;

            case 3: printf(" * Autor: Cristian Espinoza \n ");
                    printf(" * Universidad santiago de chile \n");
                    break;
            default:
                    if(opcion != 4)
                        printf("Esta opcion no esta permitida.\n");
                    break;
        }

    }while(opcion!=4);
        
}