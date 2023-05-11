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

void *forwardlist_search_place(ForwardList *l, Node *n, int position){
    int alocado = 0;

    Node *prev = NULL,
        *now = l->head,
        *next;

    while(now != NULL){
        next = (position == COLUMN) ? now->nextColumn : now->nextLine;
        
        if(position == COLUMN){
            //Organiza as colunas da matriz
            if(now->column > n->column){
                // Coluna do node menor que coluna da head
                n->nextColumn = now;
                l->head = n;
                alocado++;

            } else if(now->column > n->column && next->column < n->column){
                // Coluna do node entre atual e proximo
                now->nextColumn = n;
                n->nextColumn = next;
                alocado++;

            }

        } else{
            // Organiza as linhas da matriz
            if(now->line > n->line){
                // Linha do node menor que linha da head
                n->nextLine = now;
                l->head = n;
                alocado++;

            } else if(now->line > n->line && next->line < n->line){
                // Linha do node entre atual e proximo
                now->nextLine = n;
                n->nextLine = next;
                alocado++;

            }
        }
        
        prev = now;
        now = next;
    }

    if(!alocado){
        //caso for o ultimo do vetor
        if(position == COLUMN){
            prev->nextColumn = n;

        } else{
            prev->nextLine = n;
        }
    }
}

void forwardlist_add_Line(ForwardList *l, Node *n){
    
    Node *aux = l->head;

    while(aux->nextLine != NULL){
        aux = aux->nextLine;
    }
    
    aux->nextLine = n;
}

void forwardlist_add_Column(ForwardList *l, Node *n){

    Node *aux = l->head;

    while(aux->nextColumn != NULL){
        aux = aux->nextColumn;
    }
    
    aux->nextColumn = n;
}






void forwardlist_destroy(ForwardList *l, int size){
    Node *aux;
    for(int i = 0; i < size; i++){
        aux = (l+i)->head;
        while(aux != NULL){
            free(aux);
            aux = aux->nextLine;
        }
    }
    
    free(l);
    l = NULL;
}