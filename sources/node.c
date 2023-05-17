#include "../headers/node.h"
#include <stdio.h>
#include <stdlib.h>

Node *node_construct(data_type value, int line, int column){
    /*
        O(1), pois independente do valor e do tamanho da matriz, essa função apenas faz
        atribuições a um node
    */

    Node *n = (Node*) malloc(sizeof(Node));

    n->value = value;
    n->line = line;
    n->column = column;
    n->next_Line = n->next_Column = NULL;

    return n;
}

data_type node_return_value(Node *n, int coord, int position){
    /* O(1), pois indeoendete de qualquer tamanho, fara somente essas mesmas
        atribuições ao node *n */
    data_type aux = 0;

    if(!n) return aux;

    if(position == LINE){
        if(n->column == coord){
            aux = n->value;
            
        }
    } else if(position == COLUMN){
        if(n->line == coord){
            aux = n->value;
        }
    }

    return aux;
}

void print_node(Node *n){
    printf("\nValue %d - [%d ,%d]\n", n->value, n->line, n->column);
}


void node_destroy(Node* n){
    // O(1), pois realiza sempre a mesma função de atribuição e liberação

    free(n);
    n = NULL;
}