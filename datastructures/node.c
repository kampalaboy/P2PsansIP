#include "node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Node node_constructor(void *data, unsigned long size){
    
    if (size<1){
        printf("Not allowed");
        exit(1);
    }
    
    struct Node node;
    node.data = malloc(size);
    memcpy(node.data,data, size );
    node.previous = NULL;
    node.next =NULL;
    return node;
}
void node_destructor(struct Node *node){
        free(node->data);
        free(node);
}
