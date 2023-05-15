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
    int aux = 0;

    if(position == LINE){
        if(n && n->column == coord){
            aux = n->value;
            
        }
    } else if(position == COLUMN){
        if(n && n->line == coord){
            aux = n->value;
        }
    }

    return aux;
}

void node_swap_update(Node *n1, int new_coord1, Node *n2, int new_coord2, int position){
    /* O(N), pois percorre os nodes apenas uma vez e juntos, sendo N o tamanho da maior lista */
    Node *aux1 = n1, *aux2 = n2;

    while(aux1 || aux2){

        if(aux1){
            if(position == COLUMN){
                aux1->column = new_coord1;
                aux1 = aux1->next_Line;

            } else if(position == LINE){
                aux1->line = new_coord1;
                aux1 = aux1->next_Column;
            }
        }

        if(aux2){
            if(position == COLUMN){
                aux2->column = new_coord2;
                aux2 = aux2->next_Line;

            } else if(position == LINE){
                aux2->line = new_coord2;
                aux2 = aux2->next_Column;
            }
        }
    }
}

void node_destroy(Node* n){
    // O(1), pois realiza sempre a mesma função de atribuição e liberação

    free(n);
    n = NULL;
}