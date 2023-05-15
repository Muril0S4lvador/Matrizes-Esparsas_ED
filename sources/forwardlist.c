#include "../headers/forwardlist.h"
#include <stdio.h>
#include <stdlib.h>

ForwardList *forwardlist_construct(int size){
    /* O(N), pois inicializa as heads de acordo com o tamanho da lista */
    ForwardList *l = (ForwardList*) calloc(size, sizeof(ForwardList));

    for(int i = 0; i < size; i++){
        (l+i)->head = NULL;
    }

    return l;
}

ForwardList *forwardlist_return_list(ForwardList *l, int idx){
    /* O(1), pois apenas faz um return somando idx a uma forwardlist *l */
    return (l+idx);
}

void forwardlist_search_place(ForwardList *l, Node *n, int position){
    /* O(N^2), pois se a linha e coluna estiverem inicializadas, o programa percorre, no pior caso,
        toda a linha e coluna da matriz ate achar o lugar correto do novo node da matriz */
    int alocado = 0;

    Node *prev = NULL,
        *now = l->head,
        *next;

    while(now != NULL){
        /* Se quero definir coluna, entao ele usa elementos da mesma coluna, mas linhas diferentes e vice-versa */
        next = (position == COLUMN) ? now->next_Line : now->next_Column;

        if(now->column == n->column && now->line == n->line){
            now->value = n->value;
            alocado++;

            if(position == COLUMN) node_destroy(n);

        } else if(position == COLUMN){
            /* Organiza as colunas da Matriz */

            if(now->line > n->line){
                /* Quando achar um node *now que a linha for maior que a linha do node *n,
                    como a matriz esta em forma crescente, quer dizer que o node *n é antes 
                    do node *now na lista */

                if(prev){
                    n->next_Line = now;
                    prev->next_Line = n;

                } else {
                    n->next_Line = now;
                    l->head = n;
                }
                alocado++;

            }
        } else if(position == LINE){
            /* Organiza as linhas da Matriz */

            if(now->column > n->column){
                /* Quando achar um node *now que a coluna for maior que a coluna do node *n,
                    como a matriz esta em forma crescente, quer dizer que o node *n é antes 
                    do node *now na lista */
                    
                if(prev){
                    n->next_Column = now;
                    prev->next_Column = n;

                } else {
                    n->next_Column = now;
                    l->head = n;
                }
                alocado++;
            }
        }
        if(alocado) break;

        prev = now;
        now = next;
    }
    /* Caso no while acima nao encontre um node *now situado depois do node *n,
        como a matriz esta ordenada, significa que ele esta depois no node *now */

    if(!alocado){
        if(position == COLUMN){
            prev->next_Line = n;

        } else{
            prev->next_Column = n;
        }
    }
}

void forwardlist_remove_node(ForwardList *line, ForwardList *column, int line_remove, int column_remove){
    /* O(N), como percorre tanto a linha como a coluna juntos, seria essa a complexidade, visto que seria apenas
        a lista maior que ditaria o tempo de demora dessa função */
    Node *prev_line_node = NULL, *line_node = line->head, *next_line_node = line_node->next_Column,
        *prev_column_node = NULL, *column_node = column->head, *next_column_node = column_node->next_Line;

    int line_control = 0, column_control = 0;

    while(!column_control || !line_control){

        if(line_node->line == line_remove && line_node->column == column_remove) line_control++;
        if(column_node->column == column_remove && column_node->line == line_remove) column_control++;

        if(!column_control){
            next_column_node = column_node->next_Line;
            prev_column_node = column_node;
            column_node = next_column_node;
        }

        if(!line_control){
            next_line_node = line_node->next_Column;
            prev_line_node = line_node;
            line_node = next_line_node;
        }

        if(!line_node || !column_node){
            return;
        } 
    }

    if(!prev_line_node){
        line->head = line_node->next_Column;
    } else{
        prev_line_node->next_Column = line_node->next_Column;
    }

    if(!prev_column_node){
        column->head = column_node->next_Line;
    } else{
        prev_column_node->next_Line = column_node->next_Line;
    }

    node_destroy(line_node);
}




void forwardlist_destroy(ForwardList *l, int size){
    // O(N), pois faz o free de acordo com a quantidade de itens nao nulos na lista
    Node *aux, *next;
    
    for(int i = 0; i < size; i++){
        aux = (l+i)->head;
        
        while(aux != NULL){
            next = aux->next_Line;
            node_destroy(aux);
            aux = next;
        }
    }
    
    free(l);
    l = NULL;
}