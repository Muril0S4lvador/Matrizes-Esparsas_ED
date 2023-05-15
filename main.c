#include "headers/matriz.h"
#include <stdio.h>
#include <stdlib.h>

void print_int(data_type data){
    printf("%d ", data);
}

int main(){

    Matriz *m = matriz_construct(5, 11);

    matriz_set_value(m, 3, 1, 8);
    matriz_set_value(m, 8, 1, 4);
    
    matriz_set_value(m, 9, 2, 11);
    matriz_set_value(m, 6, 2, 6);
    
    matriz_set_value(m, 2, 3, 1);
    matriz_set_value(m, 88, 3, 8);
    
    matriz_set_value(m, 5, 4, 8);
    matriz_set_value(m, 7, 4, 3);

    matriz_set_value(m, 1, 5, 4);
    matriz_set_value(m, 8, 5, 10);

    matriz_print(m, print_int);
    matriz_dense_print(m, print_int);

    matriz_swap_columns(m, 1, 8);

    matriz_print(m, print_int);
    matriz_dense_print(m, print_int);


    matriz_destroy(m);

    return 0;
}