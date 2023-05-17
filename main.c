#include "headers/matriz.h"
#include <stdio.h>
#include <stdlib.h>

void print_int(data_type data){
    printf("%d ", data);
}

int main(){

    Matriz *m1, *m2;

    m1 = matriz_construct(10, 7);

    matriz_set_value(m1, 50, 5, 4);
    matriz_set_value(m1, 50, 5, 6);

    matriz_set_value(m1, 60, 6, 3);
    matriz_set_value(m1, 60, 6, 5);
    
    matriz_set_value(m1, 70, 7, 4);
    matriz_set_value(m1, 70, 7, 6);

    matriz_dense_print(m1, print_int);

    m2 = matriz_slice(m1, 4, 2, 8, 7);

    matriz_dense_print(m2, print_int);

    matriz_destroy(m1);
    matriz_destroy(m2);


    return 0;
}