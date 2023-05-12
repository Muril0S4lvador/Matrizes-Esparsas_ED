#include "../headers/forwardlist.h"
#include <stdio.h>
#include <stdlib.h>

ForwardList *forwardlist_construct(int size){
    ForwardList *l = (ForwardList*) calloc(size, sizeof(ForwardList));

    for(int i = 0; i < size; i++){
        (l+i)->head = NULL;
    }

    return l;
}

ForwardList *forwardlist_return_list(ForwardList *l, int idx){
    return (l+idx);
}

void forwardlist_search_place(ForwardList *l, Node *n, int position){
    int alocado = 0;
    int entra = 0;

    Node *prev = NULL,
        *now = l->head,
        *next;

    while(now != NULL){
        next = (position == COLUMN) ? now->nextLine : now->nextColumn;


        if(now->column == n->column && now->line == n->line){
            now->value = n->value;
            alocado++;

            if(position == COLUMN) node_destroy(n);

        } else if(position == COLUMN){

            //Organiza as colunas da matriz
            if(now->column > n->column){
                // Coluna do node menor que coluna da head
                n->nextLine = now;
                l->head = n;
                alocado++;

            } else if(now->column > n->column && next->column < n->column){
                // Coluna do node entre atual e proximo
                now->nextLine = n;
                n->nextLine = next;
                alocado++;
            }

        } else if(position == LINE){
            // Organiza as linhas da matriz
            if(now->line > n->line){
                // Linha do node menor que linha da head
                n->nextColumn = now;
                l->head = n;
                alocado++;

            } else if(now->line > n->line && next->line < n->line){
                // Linha do node entre atual e proximo
                now->nextColumn = n;
                n->nextColumn = next;
                alocado++;
            }
        }

        if(alocado) break;

        prev = now;
        now = next;
    }

    if(!alocado){
        //caso for o ultimo do vetor
        if(position == COLUMN){
            prev->nextLine = n;

        } else{
            prev->nextColumn = n;
        }
    }
}

void forwardlist_remove_node(ForwardList *line, ForwardList *column, int line_remove, int column_remove){
        Node *prev_line_node = NULL, *line_node = line->head, *next_line_node = line_node->nextColumn,
            *prev_column_node = NULL, *column_node = column->head, *next_column_node = column_node->nextLine;

        int line_control = 0, column_control = 0;

    while(1){

        if(line_node->line == line_remove && line_node->column == column_remove) line_control++;
        if(column_node->column == column_remove && column_node->line == line_remove) column_control++;

        if(column_control && line_control) break;

        if(!column_control){
            next_column_node = column_node->nextLine;
            prev_column_node = column_node;
            column_node = next_column_node;
        }

        if(!line_control){
            next_line_node = line_node->nextColumn;
            prev_line_node = line_node;
            line_node = next_line_node;
        }
    }

    if(!prev_line_node){
        line->head = next_line_node;
    } else{
        prev_line_node->nextColumn = next_line_node;
    }

    if(!prev_column_node){
        column->head = next_column_node;
    } else
    prev_column_node->nextLine = next_column_node;
    node_destroy(line_node);
}




void forwardlist_destroy(ForwardList *l, int size){
    Node *aux, *next;
    
    for(int i = 0; i < size; i++){
        aux = (l+i)->head;
        
        while(aux != NULL){
            next = aux->nextLine;
            node_destroy(aux);
            aux = next;
        }
    }
    
    free(l);
    l = NULL;
}