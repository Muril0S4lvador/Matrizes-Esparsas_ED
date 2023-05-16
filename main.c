#include "headers/matriz.h"
#include <stdio.h>
#include <stdlib.h>

void print_int(data_type data){
    printf("%d ", data);
}

int main(){

    Matriz *m = matriz_read();
    matriz_dense_print(m, print_int);

    Matriz *m2 = matriz_construct(3, 3);
    
    for(int i = 1; i <= m2->sizeLine; i++){
        for(int c = 1; c <=m2->sizeColumn; c++){
            matriz_set_value(m2, 1800, 2, c);
        }
    }

    m2 = matriz_multiply_by_scalar(m2, 27);

    m2 = matriz_transposed(m2);

    matriz_dense_print(m2, print_int);

    matriz_write(m2);
    matriz_destroy(m2);


    return 0;
}