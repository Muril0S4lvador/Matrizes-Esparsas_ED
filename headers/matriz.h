#ifndef _MATRIZ_H_
#define _MATRIZ_H_

#include "forwardlist.h"

typedef struct{
    // Ponteiro para as colunas
    ForwardList *Column;
    // Ponteiro para as linhas
    ForwardList *Line;
    // Numero de colunas
    int sizeColumn;
    // Numero de linhas
    int sizeLine;
} Matriz;

Matriz *matriz_construct();

/*  Implementar as abaixo */

Matriz *matriz_sum(Matriz* m1, Matriz *m2);

Matriz *matriz_multiply_by_scalar(Matriz *m, data_type scalar);

Matriz *matriz_multiply(Matriz *m1, Matriz *m2);

Matriz *matriz_multiply_point_by_point(Matriz *m1, Matriz *m2);

Matriz *matriz_slice(Matriz *m, int line_sup, int column_sup, int line_inf, int column_inf)

Matriz *matriz_transposed(Matriz *m);

Matriz *matriz_convolution(Matriz *m, Matriz *kernel);

Matriz *matriz_read();

void matriz_write(Matriz *m, char *file_name);

/* -------------------^^^^^^^---------------- */

void matriz_set_value(Matriz *m, data_type value, int line, int column);

void matriz_print_node(Matriz *m, int line, int column, void (*print_fn)(data_type));

void matriz_print(Matriz *m, void (*print_fn)(data_type));

void matriz_dense_print(Matriz *m, void (*print_fn)(data_type));

void matriz_swap(Matriz *m, int num1, int num2, int position);

void matriz_swap_columns(Matriz *m, int column1, int column2);

void matriz_swap_lines(Matriz *m, int line1, int line2);

void matriz_sort(Matriz *m, ForwardList *l, int position);

void matriz_destroy(Matriz *m);

#endif