#ifndef _MATRIZ_H_
#define _MATRIZ_H_

#include "forwardlist.h"

typedef struct{
    ForwardList *Column;
    ForwardList *Line;
    int sizeColumn;
    int sizeLine;
} Matriz;

Matriz *matriz_construct();

void matriz_add_value(Matriz *m, data_type value, int line, int column);

void matriz_print(Matriz *m, void (*print_fn)(data_type));

void matriz_dense_print(Matriz *m, void (*print_fn)(data_type));



void matriz_destroy(Matriz *m);

#endif