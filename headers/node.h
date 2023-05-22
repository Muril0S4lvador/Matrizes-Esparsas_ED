#ifndef _NODE_H_
#define _NODE_H_

#define COLUMN -1
#define LINE -2

typedef float data_type;

typedef struct Node{
    // Valor da Coluna
    int column;
    // Valor da linha
    int line;
    // Valor do node
    data_type value;
    // Elemento da proxima linha e mesma coluna
    struct Node *next_Line;
    // Elemento da proxima coluna e mesma linha
    struct Node *next_Column;
} Node;

Node *node_construct(data_type value, int line, int column);

data_type node_return_value(Node *n, int coord, int position);

void node_destroy(Node* n);

#endif