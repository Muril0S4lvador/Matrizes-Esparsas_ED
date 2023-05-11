#ifndef _forward_list_H_
#define _forward_list_H_

#include "node.h"

#define COLUMN -1
#define LINE -2

typedef struct{
    Node *head;

} ForwardList;

ForwardList *forwardlist_construct(int size);

ForwardList *forwardlist_return_list(ForwardList *l, int idx);

void *forwardlist_search_place(ForwardList *l, Node *n, int position);

void forwardlist_add_Line(ForwardList *l, Node *n);

void forwardlist_add_Column(ForwardList *l, Node *n);

void forwardlist_destroy(ForwardList *l, int size);

#endif