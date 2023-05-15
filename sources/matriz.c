#include "../headers/matriz.h"
#include <stdio.h>
#include <stdlib.h>

Matriz *matriz_construct(int line, int column){
    /*
        O(N + M), considerando N e M como numero de linhas e colunas pois as 
        funçoes forward_construct inicializam todas as heads conforme o numero 
        de linhas e colunas
    */
    Matriz *m = (Matriz*) malloc(sizeof(Matriz));

    m->sizeColumn = column;
    m->sizeLine = line;
    m->Column = forwardlist_construct(column);
    m->Line = forwardlist_construct(line);

    return m;
}

void matriz_set_value(Matriz *m, data_type value, int line, int column){
    /* O(N^2), pois, no pior cenario, a matriz percorre todos os elementos nao nulos de uma
        coluna e de uma linha ate chegar no seu lugar correto */
    Node *n;

    if(value) n = node_construct(value, line, column);

    line--;
    column--;

    ForwardList *line_list = forwardlist_return_list(m->Line, line),
        *column_list = forwardlist_return_list(m->Column, column);

    if(!line_list->head && !column_list->head && value){
        /* Adiciona node nas heads quando nem coluna e nem linha estao inicializadas com algum elemento nao nulo */
        line_list->head = column_list->head = n;

    } else if(!line_list->head && column_list->head && value){
        /* Adiciona node quando a linha nao esta inicializada */
        line_list->head = n;
        forwardlist_search_place(column_list, n, COLUMN);
            

    } else if(line_list->head && !column_list->head && value){
        /* Adiciona node quando a coluna nao esta inicializada */
        column_list->head = n;
        forwardlist_search_place(line_list, n, LINE);

    } else if(line_list->head && column_list->head){
        /* Adiciona ou remove node quando linha e coluna estao inicializadas */
        if(value){
            forwardlist_search_place(line_list, n, LINE);
            forwardlist_search_place(column_list, n, COLUMN);

        } else{
            forwardlist_remove_node(line_list, column_list, line+1, column+1);
        }
    }
}

void matriz_print_node(Matriz *m, int line, int column, void (*print_fn)(data_type)){
    /* O(N), pois essa função roda seguindo a linha, na pior das hipoteses esta na ultima coluna,
        como anda na mesma linha, N seria o número de colunas da matriz */
    ForwardList *list = forwardlist_return_list(m->Line, line-1);
    Node *aux = list->head;

    data_type value = 0;

    while(aux){

        if(aux->column == column) break;

        aux = aux->next_Column;
    }

    if(aux) value = aux->value;

    printf("\nNode: [%d, %d]\nValue: ", line, column);
    print_fn(value);
    printf("\n\n");
}

void matriz_print(Matriz *m, void (*print_fn)(data_type)){
    /* O(N), pois printa somente os itens nao nulos da matriz */

    printf("Matriz %dx%d\n", m->sizeLine, m->sizeColumn);

    ForwardList *aux_list;
    Node *aux_node, *prev;
    int help = 0, actual_column = 0;

    for(int i = 0; i < m->sizeLine; i++){
        aux_list = forwardlist_return_list(m->Line, i);
        aux_node = aux_list->head;
        help = 0;
        actual_column = 0;

        while(aux_node != NULL){

            if(aux_node->column > actual_column){
                actual_column = aux_node->column;
            } else{
                prev->next_Column = NULL;
                break;
            }

            print_fn(aux_node->value);
            prev = aux_node;
            aux_node = aux_node->next_Column;
            help = 1;
        }
        if(help) printf("\n");
    }
    printf("\n");
}

void matriz_dense_print(Matriz *m, void (*print_fn)(data_type)){
    /* O(N^2), ja que percorre todo as linhas e colunas da matriz */
    data_type value = 0;
    ForwardList *aux_list;
    Node *node, *aux_node;

    printf("Matriz densa %dx%d\n", m->sizeLine, m->sizeColumn);

    for(int l = 0; l < m->sizeLine; l++){
        aux_list = forwardlist_return_list(m->Line, l);
        node = aux_list->head;

        for(int c = 1; c <= m->sizeColumn; c++){
            value = node_return_value(node, c, LINE);
            if(value) node = node->next_Column;

            print_fn(value);
        }
        printf("\n");
    }
    printf("\n");
}

void matriz_swap_columns(Matriz *m, int column1, int column2){
    /* A mesma da função swap, reutilizei ela 2x, pois do modo que construi
        a pessoa teria que ter conhecimento de defines de dentro da biblioteca,
        dai separe em duas */
    matriz_swap(m, column1, column2, COLUMN);
}

void matriz_swap_lines(Matriz *m, int line1, int line2){
    matriz_swap(m, line1, line2, LINE);
}

void matriz_swap(Matriz *m, int num1, int num2, int position){
    /* O(N^2), pois as funções matriz_sort e node_swap_update requerem uma
        varregura da lista, até mais de uma vez */
    ForwardList *l1, *l2, aux;

    if(position == COLUMN){
        l1 = forwardlist_return_list(m->Column, num1-1);
        l2 = forwardlist_return_list(m->Column, num2-1);
        
        node_swap_update(l1->head, num2, l2->head, num1, COLUMN);

    } else if(position == LINE){
        l1 = forwardlist_return_list(m->Line, num1-1);
        l2 = forwardlist_return_list(m->Line, num2-1);

        node_swap_update(l1->head, num2, l2->head, num1, LINE);
    }

    aux.head = l1->head;
    l1->head = l2->head;
    l2->head = aux.head;


    if(position == COLUMN){
        matriz_sort(m, l1, COLUMN);
        matriz_sort(m, l2, COLUMN);

    } else if(position == LINE){
        matriz_sort(m, l1, LINE);
        matriz_sort(m, l2, LINE);
    }
}

void matriz_sort(Matriz *m, ForwardList *l, int position){
    /* O(NlogN), pois passa conferindo as linhas dos vetores cada vez */
    /* Tive que usar assim para nao desordenar a lista */
    Node *aux = l->head, *atual, *prev, *next;
    ForwardList *l_aux;

    while(aux){

        if(position == COLUMN){
            l_aux = forwardlist_return_list(m->Line, aux->line-1);
            forwardlist_search_place(l_aux, aux, LINE);
            aux = aux->next_Line;

        } else if(position == LINE){
            l_aux = forwardlist_return_list(m->Column, aux->column-1);
            forwardlist_search_place(l_aux, aux, COLUMN);
            aux = aux->next_Column;
        }
    }
}






void matriz_destroy(Matriz *m){
    /*
        O(N), pois realiza o free de acordo com a quantidade de itens no total da lista,
        mas por mais que tenha 2 funções, a segunda nao libera os nodes, apenas a lista em si
    */
    forwardlist_destroy(m->Column, m->sizeColumn);
    forwardlist_destroy(m->Line, 0);

    free(m);
    m = NULL;
}