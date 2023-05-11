#include <stdio.h>
#include <stdlib.h>
#include "forward_list.h"

// cria uma lista
ForwardList* forward_list_construct(){

    ForwardList *l = (ForwardList*) malloc(sizeof(ForwardList));
    l->head = NULL;
    l->size = 0;

    return l;
}

// retorna o número de elementos na lista
int forward_list_size(ForwardList* l){
    return l->size;
}

// adiciona um item no início da lista
void forward_list_push_front(ForwardList* l, data_type val){
    l->head = node_construct(val, l->head);
    l->size++;
}

// mostra a lista na tela
void forward_list_print(ForwardList* l, void (*print_fn)(data_type)){

    printf("[");
    Node *aux = l->head;
    while(aux != NULL){
        print_fn(aux->value);
        aux = aux->next;
        if(aux != NULL) printf(", ");
    }
    printf("]");
}

// retorna o i-ésimo elemento da lista
data_type forward_list_get(ForwardList* l, int i){
    Node *aux = l->head;

    for(int x = 0; x < i; x++){
        aux = aux->next;
    }
    
    return aux->value;
}

// remove o primeiro elemento
data_type forward_list_pop_front(ForwardList* l){

    Node *aux = l->head;
    int value = aux->value;

    l->head = l->head->next;
    free(aux);

    return value;
}

ForwardList* forward_list_reverse(ForwardList* l){

    ForwardList *l2 = forward_list_construct();

    for(int i = 0; i < l->size; i++){
        forward_list_push_front(l2, forward_list_get(l, i));
    }

    return l2;
}

/*
ForwardList* forward_list_reverse_inplace(ForwardList* l){
    
    Node *next, *ant, *now;
    now = l->head;
    ant = NULL;

    for(int i = 0; i < l->size; i++){
        next = now->next;
        now->next = ant;
        ant = now;
        now = next;
    }
    l->head = ant;

    return l;
}
*/

/* vv PARTE DOIS vv */

// remove todos os nós da lista
// void forward_list_clear(ForwardList* l);


// libera o espaço alocado para a lista
void forward_list_destroy(ForwardList* l){
    while(l->head != NULL){
        Node *aux = l->head->next;
        free(l->head);
        l->head = aux;
    }

    free(l);
}

// remove todas as ocorrências de um valor da lista
void forward_list_remove(ForwardList* l, data_type val){
    Node *ant = NULL, *now = l->head, *next;
    int size = l->size;

    for(int i = 0; i < size; i++){
        next = now->next;

        if( val == now->value ){
            if(ant != NULL)
                ant->next = next;
            else
                l->head = next;
            
            l->size--;
            free(now);

        } else{
            ant = now;
        }
        now = next;
    }

}


// remove valores duplicados de uma lista ordenada
// void forward_list_unique(ForwardList* l);


// adiciona os itens da lista m no início da lista l
// void forward_list_cat(ForwardList* l, ForwardList* m);


// ordena a lista l
// void forward_list_sort(ForwardList* l);