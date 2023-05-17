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

Matriz *matriz_swap_columns(Matriz *m, int column1, int column2){
    /* A mesma da função swap, reutilizei ela 2x, pois do modo que construi
        a pessoa teria que ter conhecimento de defines de dentro da biblioteca,
        dai separe em duas */
    return m = matriz_swap(m, column1, column2, COLUMN);
}

Matriz *matriz_swap_lines(Matriz *m, int line1, int line2){
     return m = matriz_swap(m, line1, line2, LINE);
}

Matriz *matriz_swap(Matriz *m, int num1, int num2, int position){
    /* O(N^2), pois percorre todo a lista de colunas, linha por linha */
    ForwardList *aux_list;
    Matriz *m2 = matriz_construct(m->sizeLine, m->sizeColumn);
    Node *aux_node;

    for(int i = 0; i < m->sizeLine; i++){
        aux_list = forwardlist_return_list(m->Line, i);
        aux_node = aux_list->head;
        while(aux_node){

            if(position == COLUMN){
                if(aux_node->column == num1) aux_node->column = num2;
                if(aux_node->column == num2) aux_node->column = num1;
            } else if(position == LINE){
                if(aux_node->line == num1) aux_node->line = num2;
                if(aux_node->line == num2) aux_node->line = num1;
            }

            matriz_set_value(m2, aux_node->value, aux_node->line, aux_node->column);
            aux_node = aux_node->next_Column;
        }
    }

    matriz_destroy(m);
    return m2;
}

Matriz *matriz_sum(Matriz* m1, Matriz *m2){
    Matriz *m3;
    if(m1->sizeLine == m2->sizeLine && m1->sizeColumn == m2->sizeLine)
        m3 = matriz_construct(m1->sizeLine, m1->sizeColumn);

    else{
        printf("Arrays must be of the same dimension!\n");
        return NULL;
    }

    ForwardList *list_m1, *list_m2;
    Node *node_m1, *node_m2, node_m3;
    int value_m1, value_m2;

    for(int l = 0; l < m1->sizeLine; l++){
        list_m1 = forwardlist_return_list(m1->Line, l);
        list_m2 = forwardlist_return_list(m2->Line, l);

        node_m1 = list_m1->head;
        node_m2 = list_m2->head;

        while(node_m1 || node_m2){

            if(node_m1 && !node_m2){
                matriz_set_value(m3, node_m1->value, node_m1->line, node_m1->column);
                node_m1 = node_m1->next_Column;

            } else if(!node_m1 && node_m2){
                matriz_set_value(m3, node_m2->value, node_m2->line, node_m2->column);
                node_m2 = node_m2->next_Column;

            } else if(node_m1->column > node_m2->column){
                matriz_set_value(m3, node_m2->value, node_m2->line, node_m2->column);
                node_m2 = node_m2->next_Column;

            } else if(node_m1->column < node_m2->column){
                matriz_set_value(m3, node_m1->value, node_m1->line, node_m1->column);
                node_m1 = node_m1->next_Column;
                
            } else if(node_m1->column == node_m2->column){
                matriz_set_value(m3, node_m1->value + node_m2->value, node_m1->line, node_m1->column);
                node_m1 = node_m1->next_Column;
                node_m2 = node_m2->next_Column;
            }
        }
    }

    return m3;
}

Matriz *matriz_multiply_by_scalar(Matriz *m, data_type scalar){

    ForwardList *aux_list;
    Node *aux_node;
    Matriz *m2 = matriz_construct(m->sizeLine, m->sizeColumn);

    for(int i = 0; i < m->sizeLine; i++){
        aux_list = forwardlist_return_list(m->Line, i);
        aux_node = aux_list->head;

        while(aux_node != NULL){
            aux_node->value *= scalar;
            matriz_set_value(m2, aux_node->value, aux_node->line, aux_node->column);
            aux_node = aux_node->next_Column;
        }
    }
    matriz_destroy(m);
    
    return m2;
}

Matriz *matriz_multiply(Matriz *m1, Matriz *m2){
    if(m1->sizeColumn != m2->sizeLine) return NULL;
    
    Matriz *m3 = matriz_construct(m1->sizeLine, m2->sizeColumn);
    ForwardList *line_m1, *column_m2;
    Node *n1, *n2;
    data_type value = 0;
    int haha = 1;

    for(int l = 0; l < m1->sizeLine; l++){
        line_m1 = forwardlist_return_list(m1->Line, l);

        for(int c = 0; c < m2->sizeColumn; c++){
            column_m2 = forwardlist_return_list(m2->Column, c);
            n1 = line_m1->head;
            n2 = column_m2->head;
            value = 0;

            while(n1 && n2){

                if(n1->column == n2->line && haha){
                    value += n1->value * n2->value;
                    n1 = n1->next_Column;
                    n2 = n2->next_Line;

                } else if(n1->column > n2->line && haha){
                    n2 = n2->next_Line;

                } else if(n1->column < n2->line && haha){
                    n1 = n1->next_Column;
                }
            }
            if(value){
                matriz_set_value(m3, value, l+1, c+1);
            }
        }
    }
    return m3;
}

Matriz *matriz_multiply_point_by_point(Matriz *m1, Matriz *m2){
    Matriz *m3;
    if(m1->sizeLine == m2->sizeLine && m1->sizeColumn == m2->sizeLine)
        m3 = matriz_construct(m1->sizeLine, m1->sizeColumn);

    else{
        printf("Arrays must be of the same dimension!\n");
        return NULL;
    }

    ForwardList *list_m1, *list_m2;
    Node *node_m1, *node_m2, node_m3;
    int value_m1, value_m2;

    for(int l = 0; l < m1->sizeLine; l++){
        list_m1 = forwardlist_return_list(m1->Line, l);
        list_m2 = forwardlist_return_list(m2->Line, l);

        node_m1 = list_m1->head;
        node_m2 = list_m2->head;

        while(node_m1 && node_m2){

            if(node_m1->column > node_m2->column){
                node_m2 = node_m2->next_Column;

            } else if(node_m1->column < node_m2->column){
                node_m1 = node_m1->next_Column;
                
            } else if(node_m1->column == node_m2->column){
                matriz_set_value(m3, node_m1->value * node_m2->value, node_m1->line, node_m1->column);
                node_m1 = node_m1->next_Column;
                node_m2 = node_m2->next_Column;
            }
        }
    }

    return m3;
}

Matriz *matriz_transposed(Matriz *m){

    ForwardList *aux_list;
    Node *aux_node;
    Matriz *m2 = matriz_construct(m->sizeColumn, m->sizeLine);

    for(int i = 0; i < m->sizeLine; i++){
        aux_list = forwardlist_return_list(m->Line, i);
        aux_node = aux_list->head;

        while(aux_node != NULL){
            matriz_set_value(m2, aux_node->value, aux_node->column, aux_node->line);
            aux_node = aux_node->next_Column;
        }
    }
    matriz_destroy(m);
    
    return m2;
}

Matriz *matriz_slice(Matriz *m, int line_sup, int column_sup, int line_inf, int column_inf){
    if(line_sup > line_inf && column_sup > column_inf){
        printf("ERROR: Invalid coordinates\n");
        return NULL;
    }

    Matriz *m2 = matriz_construct(line_inf - line_sup + 1, column_inf - column_sup + 1);
    ForwardList *aux_list;
    Node *n;
    for(int i = line_sup - 1; i < line_inf; i++){
        aux_list = forwardlist_return_list(m->Line, i);
        n = aux_list->head;

        while(n){
            if(n->column >= column_sup && n->column <= column_inf){
                matriz_set_value(m2, n->value, n->line - line_sup + 1, n->column - column_sup + 1);
            }
            n = n->next_Column;
            if(n && n->column > column_inf) break;
        }
    }
    return m2;
}






Matriz *matriz_read(){
    Matriz *m;

    FILE *arq = fopen("Matriz.bin", "rb");
    int line, column, value;

    if(!arq) return NULL;

    fread(&line, sizeof(int), 1, arq);
    fread(&column, sizeof(int), 1, arq);

    m = matriz_construct(line, column);
    printf("Linhas %d e colunas %d\n", line, column);

    while(!feof(arq)){
        fread(&value, 1, sizeof(int),arq);
        fread(&line, 1, sizeof(int),arq);
        fread(&column, 1, sizeof(int),arq);
        matriz_set_value(m, value, line, column);
    }

    fclose(arq);
    return m;
}

void matriz_write(Matriz *m){
    char *file_name = "Matriz.bin";
    FILE *arq = fopen(file_name, "wb");

    Node *aux_node;
    ForwardList *aux_list;
    int qtd = 0;
    int line = m->sizeLine, column = m->sizeColumn;

    fwrite(&line, 1, sizeof(int), arq);
    fwrite(&column, 1, sizeof(int), arq);
    // fwrite(&qtd, 1, sizeof(int), arq);
    
    for(int i = 0; i < m->sizeLine; i++){
        aux_list = forwardlist_return_list(m->Line, i);
        aux_node = aux_list->head;

        while(aux_node){
            fwrite(&aux_node->value, 1, sizeof(int),arq);
            fwrite(&aux_node->line, 1, sizeof(int),arq);
            fwrite(&aux_node->column, 1, sizeof(int),arq);
            aux_node = aux_node->next_Column;
        }
    }

    fclose(arq);
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