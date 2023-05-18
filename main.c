#include "headers/matriz.h"
#include <stdio.h>
#include <stdlib.h>

void print_int(data_type data){
    printf("%d ", data);
}

int main(){

    Matriz *m1, *kernel;
    int x = 2;
    data_type value;

    m1 = matriz_construct(6, 6);

    for(int l = 1; l <= m1->sizeLine; l++){
        for(int c = 1; c <= m1->sizeColumn; c++){
            scanf("%d", &value);
            matriz_set_value(m1, value, l, c);
        }
    }

    matriz_dense_print(m1, print_int);

    kernel = matriz_construct(3, 3);
    printf("KERNEL\n");
    matriz_set_value(kernel, 1, 1, 1);
    matriz_set_value(kernel, 1, 2, 1);
    matriz_set_value(kernel, 1, 3, 1);
    matriz_set_value(kernel, -1, 1, 3);
    matriz_set_value(kernel, -1, 2, 3);
    matriz_set_value(kernel, -1, 3, 3);

    matriz_dense_print(kernel, print_int);

    Matriz *conv = matriz_convolution(m1, kernel, print_int);

    matriz_dense_print(conv, print_int);

    matriz_destroy(m1);

    return 0;
}