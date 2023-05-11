#include "../headers/matriz.h"
#include <stdio.h>
#include <stdlib.h>

Matriz *matriz_construct(int line, int column){
    Matriz *m = (Matriz*) malloc(sizeof(Matriz));

    m->sizeColumn = column;
    m->sizeLine = line;
    m->Column = forwardlist_construct(column);
    m->Line = forwardlist_construct(line);

    return m;
}

void matriz_add_value(Matriz *m, data_type value, int line, int column){
    Node *n = node_construct(value, line, column);

    line--;
    column--;

    ForwardList *line_list = forwardlist_return_list(m->Line, line),
        *column_list = forwardlist_return_list(m->Column, column);

    if(!line_list->head && !column_list->head){
        // Adiciona o node n nas heads
        line_list->head = column_list->head = n;

    } else if(!line_list->head && column_list->head){
        line_list->head = n;
        forwardlist_search_place(column_list, n, COLUMN);
            

    } else if(line_list->head && !column_list->head){
        column_list->head = n;
        forwardlist_search_place(line_list, n, LINE);

    } else{
        forwardlist_search_place(line_list, n, LINE);
        forwardlist_search_place(column_list, n, COLUMN);
        
    }
}

void matriz_print(Matriz *m){

    printf("Matriz %dx%d\n", m->sizeLine, m->sizeColumn);

    ForwardList *aux_list;
    Node *aux_node;

    for(int i = 0; i < m->sizeLine; i++){
        aux_list = forwardlist_return_list(m->Column, i);
        aux_node = aux_list->head;

        while(aux_node != NULL){
            printf("%d ", aux_node->value);
            aux_node = aux_node->nextColumn;
        }
        printf("\n");
    }
}







void matriz_destroy(Matriz *m){
    forwardlist_destroy(m->Line, m->sizeLine);

    free(m->Column);
    free(m);
    m->Column = NULL;
    m = NULL;
}