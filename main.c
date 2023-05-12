#include "headers/matriz.h"
#include <stdio.h>
#include <stdlib.h>

void print_int(data_type data){
    printf("%d ", data);
}

int main(){

    int linha = 5, coluna = 5;

    Matriz *h = matriz_construct(10, 10);

    for(int i = 1; i <= h->sizeLine; i++){
        for(int j = 1; j <= h->sizeColumn; j++){
            if(j == i)
                matriz_set_value(h, (10*i+j), i, j);
        }
    }
    
    matriz_dense_print(h, print_int);

    matriz_print(h, print_int);

    matriz_swap(h, 1, 5, COLUMN);
    matriz_swap(h, 2, 4, COLUMN);

    matriz_dense_print(h, print_int);

    matriz_print(h, print_int);

    matriz_swap(h, 2, 4, LINE);
    matriz_swap(h, 1, 5, LINE);

    matriz_dense_print(h, print_int);

    matriz_destroy(h);

    return 0;
}