#include "headers/matriz.h"
#include <stdio.h>
#include <stdlib.h>

void print_float(data_type data){
    printf("%.1f ", data);
}

int main(){

    Matriz *m1 = matriz_read("Matrizes/kernel"), 
        *m2 = matriz_read("Matrizes/Matriz3"),
        *m3 = matriz_sum(m1, m2),
        *m4, *m5;

    printf("\nTeste das funções de ler matrizes em binario e dense_print e print como esparsa\n\n");

    matriz_dense_print(m1, print_float);
    matriz_dense_print(m2, print_float);
    matriz_dense_print(m3, print_float);

    matriz_print(m1, print_float);

    printf("Teste das funções swap lines e columns\n\n");

    m4 = matriz_swap_lines(m1, 1, 4);
    m5 = matriz_swap_columns(m1, 2, 5);
    matriz_print(m4, print_float);
    matriz_print(m5, print_float);

    matriz_destroy(m4);
    matriz_destroy(m5);

    printf("Testando printar um nó usando apenas a linha e coluna dele\n\n");

    matriz_print_node(m3, 1, 4, print_float);

    printf("Matriz Transposta\n\n");

    m4 = matriz_transposed(m3);
    matriz_print(m4, print_float);

    printf("Matriz multiplicada por um escalar\n\n");

    m5 = matriz_multiply_by_scalar(m4, 2.75);
    matriz_print(m5, print_float);

    printf("Matriz slice\n\n");

    matriz_destroy(m3);
    m3 = matriz_slice(m5, 2, 2, 3, 4);
    matriz_dense_print(m3, print_float);
    matriz_destroy(m3);

    printf("Matriz convolution, write e read\n\n");

    m3 = matriz_read("Matrizes/Matriz1");
    Matriz *m6 = matriz_convolution(m3, m1);
    matriz_print(m6, print_float);
    matriz_write(m6, "Matrizes/Matriz4");
    matriz_destroy(m6);
    m6 = matriz_read("Matrizes/Matriz4");
    matriz_dense_print(m6, print_float);

    printf("Matriz multiply\n\n");

    Matriz *m7 = matriz_read("Matrizes/Matriz2"),
        *m8 = matriz_multiply(m7, m3);

    matriz_dense_print(m8, print_float);


    matriz_destroy(m1);
    matriz_destroy(m2);
    matriz_destroy(m3);
    matriz_destroy(m4);
    matriz_destroy(m5);
    matriz_destroy(m6);
    matriz_destroy(m7);
    matriz_destroy(m8);

    return 0;
}


/* Saída esperada(nessa main coloquei todas as funções implementadas para rodar):

Teste das funções de ler matrizes em binario e dense_print e print como esparsa

Matriz densa 5x5
0.0 0.0 0.0 0.0 0.0
0.0 0.0 0.0 0.0 0.0
0.0 0.0 0.0 0.0 0.0
0.0 8.0 0.0 5.0 4.0
0.0 8.0 0.0 0.0 0.0

Matriz densa 5x5
12.0 0.0 0.0 7.0 0.0
0.0 3.0 0.0 6.0 0.0
4.0 0.0 0.0 5.0 0.0
0.0 5.0 0.0 0.0 6.0
0.0 0.0 66.0 8.0 0.0

Matriz densa 5x5
12.0 0.0 0.0 7.0 0.0
0.0 3.0 0.0 6.0 0.0
4.0 0.0 0.0 5.0 0.0
0.0 13.0 0.0 5.0 10.0
0.0 8.0 66.0 8.0 0.0

Matriz 5x5
[4, 2] - 8.0 | [4, 4] - 5.0 | [4, 5] - 4.0 |
[5, 2] - 8.0 |

Teste das funções swap lines e columns

Matriz 5x5
[1, 2] - 8.0 | [1, 4] - 5.0 | [1, 5] - 4.0 |
[5, 2] - 8.0 |

Matriz 5x5
[4, 2] - 4.0 | [4, 4] - 5.0 | [4, 5] - 8.0 |
[5, 5] - 8.0 |

Testando printar um nó usando apenas a linha e coluna dele


Node: [1, 4]
Value: 7.0

Matriz Transposta

Matriz 5x5
[1, 1] - 12.0 | [1, 3] - 4.0 |
[2, 2] - 3.0 | [2, 4] - 13.0 | [2, 5] - 8.0 |
[3, 5] - 66.0 |
[4, 1] - 7.0 | [4, 2] - 6.0 | [4, 3] - 5.0 | [4, 4] - 5.0 | [4, 5] - 8.0 |
[5, 4] - 10.0 |

Matriz multiplicada por um escalar

Matriz 5x5
[1, 1] - 33.0 | [1, 3] - 11.0 |
[2, 2] - 8.2 | [2, 4] - 35.8 | [2, 5] - 22.0 |
[3, 5] - 181.5 |
[4, 1] - 19.2 | [4, 2] - 16.5 | [4, 3] - 13.8 | [4, 4] - 13.8 | [4, 5] - 22.0 |
[5, 4] - 27.5 |

Matriz slice

Matriz densa 2x3
8.2 0.0 35.8
0.0 0.0 0.0

Matriz convolution, write e read

Matriz 5x20
[1, 2] - 32.0 | [1, 3] - 20.0 | [1, 4] - 55.0 | [1, 5] - 48.0 | [1, 6] - 56.0 | [1, 7] - 44.0 | [1, 8] - 29.0 | [1, 9] - 64.0 | [1, 10] - 48.0 | [1, 11] - 56.0 | [1, 13] - 68.0 | [1, 14] - 25.0 | [1, 15] - 8.0 | [1, 16] - 62.0 | [1, 17] - 47.0 | [1, 18] - 16.0 | [1, 19] - 32.0 | [1, 20] - 16.0 |
[2, 1] - 25.0 | [2, 2] - 105.0 | [2, 3] - 38.0 | [2, 4] - 40.0 | [2, 5] - 60.0 | [2, 6] - 15.0 | [2, 7] - 20.0 | [2, 8] - 77.0 | [2, 9] - 75.0 | [2, 10] - 64.0 | [2, 11] - 158.0 | [2, 12] - 40.0 | [2, 13] - 48.0 | [2, 14] - 32.0 | [2, 15] - 20.0 | [2, 16] - 4.0 | [2, 17] - 45.0 | [2, 18] - 10.0 | [2, 19] - 8.0 | [2, 20] - 48.0 |
[3, 2] - 56.0 | [3, 6] - 20.0 | [3, 7] - 25.0 | [3, 8] - 36.0 | [3, 9] - 105.0 | [3, 10] - 25.0 | [3, 11] - 80.0 | [3, 12] - 106.0 | [3, 13] - 40.0 | [3, 14] - 16.0 | [3, 16] - 24.0 | [3, 17] - 48.0 | [3, 18] - 20.0 | [3, 20] - 32.0 |
[4, 9] - 28.0 | [4, 10] - 55.0 | [4, 11] - 25.0 | [4, 12] - 56.0 | [4, 13] - 52.0 | [4, 14] - 31.0 | [4, 15] - 20.0 | [4, 16] - 24.0 | [4, 17] - 32.0 | [4, 18] - 12.0 | [4, 19] - 15.0 |

Matriz densa 5x20
0.0 32.0 20.0 55.0 48.0 56.0 44.0 29.0 64.0 48.0 56.0 0.0 68.0 25.0 8.0 62.0 47.0 16.0 32.0 16.0
25.0 105.0 38.0 40.0 60.0 15.0 20.0 77.0 75.0 64.0 158.0 40.0 48.0 32.0 20.0 4.0 45.0 10.0 8.0 48.0
0.0 56.0 0.0 0.0 0.0 20.0 25.0 36.0 105.0 25.0 80.0 106.0 40.0 16.0 0.0 24.0 48.0 20.0 0.0 32.0
0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 28.0 55.0 25.0 56.0 52.0 31.0 20.0 24.0 32.0 12.0 15.0 0.0
0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0

Matriz multiply

Matriz densa 10x20
0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0
0.0 0.0 0.0 6.0 0.0 6.0 42.0 0.0 0.0 0.0 24.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 24.0
24.0 0.0 0.0 0.0 18.0 0.0 0.0 48.0 6.0 0.0 35.0 25.0 0.0 0.0 45.0 20.0 12.0 18.0 0.0 15.0
0.0 8.0 40.0 48.0 0.0 0.0 24.0 0.0 40.0 56.0 0.0 48.0 0.0 0.0 0.0 32.0 0.0 8.0 16.0 0.0
39.0 0.0 0.0 0.0 24.0 0.0 0.0 69.0 8.0 9.0 40.0 25.0 2.0 0.0 55.0 20.0 16.0 24.0 4.0 15.0
21.0 0.0 0.0 0.0 0.0 0.0 0.0 15.0 0.0 27.0 15.0 0.0 6.0 0.0 0.0 0.0 0.0 0.0 12.0 0.0
0.0 9.0 45.0 54.0 0.0 0.0 27.0 0.0 45.0 63.0 0.0 54.0 0.0 0.0 0.0 36.0 0.0 9.0 18.0 0.0
0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0
63.0 8.0 40.0 48.0 0.0 0.0 24.0 45.0 40.0 137.0 45.0 48.0 18.0 0.0 0.0 32.0 0.0 8.0 52.0 0.0
16.0 0.0 0.0 1.0 12.0 1.0 7.0 32.0 4.0 0.0 18.0 10.0 0.0 0.0 26.0 8.0 8.0 12.0 0.0 10.0
*/