#include "queue.h"

void push(struct Queue *queue, void *data, unsigned long size);
void * peek(struct Queue *queue);
void pop (struct Queue *queue);

struct Queue queue_constructor(){
    
    struct Queue queue;
    queue.list = linked_list_constructor();

     queue.push = push;
     queue.peek = peek;
     queue.pop = pop;

     return queue;
}

void push(struct Queue *queue, void *data, unsigned long size){

    queue->list.insert(&queue->list, &queue->list.length, &data, size);
}

void * peek(struct Queue *queue){

    void *data = queue->list.retrieve(&queue->list, 0);
    return data;
}

void pop(struct Queue *queue){

    queue->list.remove(&queue->list, 0);
}