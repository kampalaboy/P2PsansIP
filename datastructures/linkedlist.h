#ifndef LinkedList_h
#define LinkedList_h

#include "node.h"
struct LinkedList{

    struct Node *head;

    int length;

    void (*insert)(struct LinkedList *linkedlist, int index, void *data, unsigned long size);
    void (*remove)(struct LinkedList *linkedlist, int index);
    void * (*retrieve)(struct LinkedList *linkedlist, int index);
    void (*sort)(struct LinkedList *linked_list, int (*compare)(void *a, void *b));
    short (*search)(struct LinkedList *linked_list, void *query, int (*compare)(void *a, void *b));
};

struct LinkedList linked_list_constructor(void);
void linked_list_destructor(struct LinkedList *linked_list);

#endif