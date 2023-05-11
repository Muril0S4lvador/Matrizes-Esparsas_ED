#include "../headers/node.h"
#include <stdio.h>
#include <stdlib.h>

Node *node_construct(data_type value, int line, int column){
    
    Node *n = (Node*) malloc(sizeof(Node));

    n->value = value;
    n->line = line;
    n->column = column;
    n->nextLine = n->nextColumn = NULL;

    node_print(n);

    return n;
}

void node_print(Node *n){
    printf("Node:\n");
    printf("Value: %d\n[Line, Column] : [%d, %d]\n", n->value, n->line, n->column);
    if(!n->nextColumn && !n->nextLine)
    printf("(NULL, NULL)\n");
}

void node_destroy(Node* n){
    free(n);
    n = NULL;
}