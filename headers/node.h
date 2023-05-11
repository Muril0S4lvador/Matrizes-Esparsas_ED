#ifndef _NODE_H_
#define _NODE_H_

typedef int data_type;

typedef struct Node{
    int column;
    int line;
    data_type value;
    struct Node *nextLine;
    struct Node *nextColumn;
} Node;

Node *node_construct(data_type value, int line, int column);

void node_print(Node *n);

void node_destroy(Node* n);

#endif