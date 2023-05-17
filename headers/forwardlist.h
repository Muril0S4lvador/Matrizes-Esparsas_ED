#ifndef _forward_list_H_
#define _forward_list_H_

#include "node.h"

typedef struct{
    Node *head;

} ForwardList;

ForwardList *forwardlist_construct(int size);

ForwardList *forwardlist_return_list(ForwardList *l, int idx);

void forwardlist_search_place(ForwardList *l, Node *n, int position);

void forwardlist_remove_node(ForwardList *line, ForwardList *column, int line_remove, int column_remove);

void forwardlist_destroy(ForwardList *l, int size);

#endif