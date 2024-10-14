#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

struct Node * createNode(void *data, unsigned long size);
void destroyNode(struct Node *node);

struct Node * iterateLL(struct LinkedList *linkedlist, int index);
void insertNode(struct LinkedList *linkedlist, int index, void *data, unsigned long size);
void removeNode(struct LinkedList *linkedlist, int index);
void * retrieveNode(struct LinkedList *linkedlist, int index);
void sortLL(struct LinkedList *linkedlist, int (*compare)(void *a, void *b));
short bSearch(struct LinkedList *linkedlist, void *query, int (*compare)(void *a, void *b));

struct LinkedList linked_list_constructor(){
    
    struct LinkedList newList;
    newList.head = NULL;
    newList.length = 0;

    newList.insert = insertNode;
    newList.remove = removeNode;
    newList.retrieve = retrieveNode;
    newList.sort = sortLL;
    newList.search = bSearch;

    return newList;

}

void linked_list_destructor(struct LinkedList *linkedlist)
{
    for (int i = 0; i < linkedlist->length; i++)
    {
        linkedlist->remove(linkedlist, 0);
    }
}


struct Node * createNode(void *data, unsigned long size){

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    *newNode = node_constructor(data, size);
    return newNode;
}

void destroyNode(struct Node *nodeDestroy)
{
    node_destructor(nodeDestroy);
}

struct Node * iterateLL(struct LinkedList *linkedlist, int index){

    if (index < 0 || index >= linkedlist->length){
        return NULL;
    }

    struct Node *cursor = linkedlist->head;
    for (int i=0; i<index; i++){
        cursor = cursor->next;
    }
    return cursor;
}

void insertNode (struct LinkedList *linkedlist, int index, void *data, unsigned long size ){
    
    struct Node *nodeInsert = createNode(data, size);
    
    if (index == 0){
        nodeInsert->next = linkedlist->head;
        linkedlist->head = nodeInsert;
    }else{

    struct Node *cursor = iterateLL(linkedlist, index-1);
    
    nodeInsert->next = cursor->next;
    cursor->next = nodeInsert;
    }
    linkedlist->length += 1;
}

void removeNode (struct LinkedList *linkedlist, int index ){

    struct Node *nodeRemove = linkedlist->head;
    if(index == 0){

        if (nodeRemove){
        linkedlist->head = nodeRemove ->next;
        destroyNode(nodeRemove);
        }
    }else{

    struct Node *cursor = iterateLL(linkedlist, index-1);
    cursor->next = nodeRemove->next;
     destroyNode(nodeRemove);
    }
    linkedlist->length -= 1;
}

void * retrieveNode(struct LinkedList *linkedlist, int index){

    struct Node *cursor = iterateLL(linkedlist, index);

    if(index == 0){

        return cursor->data;
    }else{

        return NULL;
    }
}


void sortLL(struct LinkedList *linkedlist, int (*compare)(void *a, void *b)){
    for (struct Node *i = linkedlist->retrieve(linkedlist, 0); i; i = i->next)
    {
        for (struct Node *n = i->next; n; n = n->next)
        {
            if (compare(i->data, n->data) > 0)
            {
               // Swap them.
                void *temporary = n->data;
                n->data = i->data;
                i->data = temporary;
            }
        }
    }
}

short bSearch(struct LinkedList *linked_list, void *query, int (*compare)(void *a, void *b))
{
    int position = linked_list->length/2;
    int min_checked = 0;
    int max_checked = linked_list->length;
    while (max_checked > min_checked)
    {
        void *data = linked_list->retrieve(linked_list, position);
        if (compare(data, query) == 1)
        {
            max_checked = position;
            if (position != (min_checked + position) / 2)
            {
                position = (min_checked + position) / 2;
            }
            else
            {
                break;
            }
        }
        else if (compare(data, query) == -1)
        {
            min_checked = position;
            if (position != (max_checked + position) / 2)
            {
                position = (max_checked + position) / 2;
            }
            else
            {
                break;
            }
        }
        else
        {
            return 1;
        }
    }
    return 0;
}
