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

    if(!line_list->head && !column_list->head && value){
        // Adiciona o node n nas heads
        line_list->head = column_list->head = n;

    } else if(!line_list->head && column_list->head && value){
        // Adiciona node quando a linha nao esta inicializada
        line_list->head = n;
        forwardlist_search_place(column_list, n, COLUMN);
            

    } else if(line_list->head && !column_list->head && value){
        // Adiciona node quando a coluna nao esta inicializada
        column_list->head = n;
        forwardlist_search_place(line_list, n, LINE);

    } else if(line_list->head && column_list->head){
        // Adiciona ou remove node quando linha e coluna estao inicializadas
        if(value){
            forwardlist_search_place(line_list, n, LINE);
            forwardlist_search_place(column_list, n, COLUMN);

        } else{
            forwardlist_remove_node(line_list, column_list, n->line, n->column);
            node_destroy(n);
        }
    }
}

void matriz_print(Matriz *m, void (*print_fn)(data_type)){

    printf("Matriz %dx%d\n", m->sizeLine, m->sizeColumn);

    ForwardList *aux_list;
    Node *aux_node;

    for(int i = 0; i < m->sizeLine; i++){
        aux_list = forwardlist_return_list(m->Line, i);
        aux_node = aux_list->head;

        while(aux_node != NULL){
            print_fn(aux_node->value);
            aux_node = aux_node->nextColumn;
        }
        printf("\n");

    }
    printf("\n");
}

void matriz_dense_print(Matriz *m, void (*print_fn)(data_type)){
    data_type aux = 0;
    ForwardList *aux_list;
    Node *node;

    printf("Matriz %dx%d\n", m->sizeLine, m->sizeColumn);

    for(int l = 0; l < m->sizeLine; l++){
        aux_list = forwardlist_return_list(m->Line, l);
        node = aux_list->head;

        for(int c = 1; c <= m->sizeColumn; c++){
            aux = 0;
            if(node && node->column == c){
                aux = node->value;
                node = node->nextColumn;
            }
            print_fn(aux);
        }
        printf("\n");
    }
    printf("\n");
}







void matriz_destroy(Matriz *m){
    forwardlist_destroy(m->Column, m->sizeColumn);
    forwardlist_destroy(m->Line, 0);

    free(m);
    m = NULL;
}