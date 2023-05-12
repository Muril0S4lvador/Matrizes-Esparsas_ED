#include "headers/matriz.h"
#include <stdio.h>
#include <stdlib.h>

void print_int(data_type data){
    printf("%d ", data);
}

int main(){

    /*
    int linha, coluna;
    printf("Escreva numero de linhas e colunas dsejados (l c)");
    scanf("%d %d", &linha, &coluna);
    Matriz *m = matriz_construct(linha, coluna);
    */
   int linha = 10, coluna = 6;

    // Matriz *m = matriz_construct(linha, coluna);
    // printf("Feita a matriz %dx%d\n\n", linha, coluna);

/*
    for(int i = 1; i <= linha; i++){
        for(int j = 1; j <= coluna; j++){
            matriz_add_value(m, 1, i, j);
        }
    }
*/

    // matriz_print(m, print_int);
    // matriz_add_value(m, 0, 10, 6);

    Matriz *h = matriz_construct(10, 30);
    matriz_add_value(h , 22, 2, 2);
    matriz_add_value(h , 12, 1, 2);
    matriz_add_value(h , 98, 9, 8);
    matriz_add_value(h , 71, 7, 1);
    matriz_add_value(h , 27, 4, 10);
    matriz_add_value(h , 40, 5, 10);
    matriz_add_value(h , 10, 7, 10);
    matriz_add_value(h , 4550, 9, 10);
    matriz_dense_print(h, print_int);

    matriz_print(h, print_int);

    matriz_add_value(h , 0, 2, 2);
    matriz_add_value(h , 0, 1, 2);
    matriz_add_value(h , 0, 9, 8);
    matriz_add_value(h , 0, 7, 1);
    matriz_add_value(h , 0, 4, 10);
    matriz_add_value(h , 0, 5, 10);
    matriz_add_value(h , 0, 7, 10);
    matriz_add_value(h , 0, 9, 10);
    matriz_dense_print(h, print_int);

    matriz_print(h, print_int);

    matriz_destroy(h);
    // printf("Destruida a matriz %dx%d\n", linha, coluna);


    return 0;
}