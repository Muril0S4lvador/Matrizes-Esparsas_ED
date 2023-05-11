#include "headers/matriz.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

    /*
    int linha, coluna;
    printf("Escreva numero de linhas e colunas dsejados (l c)");
    scanf("%d %d", &linha, &coluna);
    Matriz *m = matriz_construct(linha, coluna);
    */

    Matriz *m = matriz_construct(10, 10);
    printf("Feita a matriz %dx%d\n\n", 10, 10);

    matriz_add_value(m, 1, 1, 1);
    matriz_add_value(m, 2, 2, 1);
    matriz_add_value(m, 3, 3, 1);
    matriz_add_value(m, 4, 4, 1);
    matriz_add_value(m, 5, 5, 1);
    matriz_add_value(m, 6, 6, 1);
    matriz_add_value(m, 7, 7, 1);
    matriz_add_value(m, 8, 8, 1);
    matriz_add_value(m, 9, 9, 1);
    matriz_add_value(m, 10, 10, 1);

    matriz_add_value(m, 2, 2, 4);
    matriz_add_value(m, 3, 3, 4);
    matriz_add_value(m, 4, 4, 4);
    matriz_add_value(m, 5, 5, 4);
    matriz_add_value(m, 6, 6, 4);
    matriz_add_value(m, 7, 7, 4);
    matriz_add_value(m, 8, 8, 4);
    matriz_add_value(m, 9, 9, 4);
    matriz_add_value(m, 10, 10, 4);

    matriz_print(m);


    matriz_add_value(m, 100, 1, 2);
    matriz_add_value(m, 200, 2, 2);
    matriz_add_value(m, 300, 3, 2);
    matriz_add_value(m, 400, 4, 2);
    matriz_add_value(m, 500, 5, 2);
    matriz_add_value(m, 600, 6, 2);
    matriz_add_value(m, 700, 7, 2);
    matriz_add_value(m, 800, 8, 2);
    matriz_add_value(m, 900, 9, 2);
    matriz_add_value(m, 1000, 10, 2);

    matriz_print(m);

    matriz_destroy(m);
    printf("Destruida a matriz %dx%d\n", 10, 10);


    return 0;
}