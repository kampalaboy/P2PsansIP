#ifndef Queue_h
#define Queue_h

#include "linkedlist.h"
struct Queue{

    struct LinkedList list;

    void (*push)(struct Queue *queue, void *data, unsigned long size);
    void * (*peek)(struct Queue *queue);
    void (*pop)(struct Queue *queue);
};

    struct Queue queue_constructor(void);
    struct Queue queue_destructor(struct Queue *queue);
#endif