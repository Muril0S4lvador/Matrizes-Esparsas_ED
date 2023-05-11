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

void matriz_add_value(Matriz *m, data_type value, int column, int line);

void matriz_destroy(Matriz *m);

void matriz_print(Matriz *m);


#endif