#include "network/server.h"
#include "network/server.c"
#include "network/client.h"
#include "network/client.c"
#include "systems/thread.h"
#include "datastructures/linkedlist.h"
#include "datastructures/linkedlist.c"
#include "datastructures/node.c"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


void * server_peer(void *arg){

    struct LinkedList *known_hosts = arg;

    printf("Starting Peer Server...\n");
    struct Server serving = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 1248, 20 );
    struct sockaddr *address = (struct sockaddr *)&serving.address; 
    socklen_t add_len = (socklen_t)sizeof(serving.address);
    while (1){
        int client = accept(serving.socket, address, &add_len);
        char request[255];
        memset(request, 8, 255);
        read(client, request, 255);
        char *client_add = inet_ntoa(serving.address.sin_addr);
        printf("\t\t %s says: %s\n", client_add, request);
        close(client);

        short found = 0;
        for (int i=0; i<known_hosts->length&&!found; i++){
            if(strcmp(client_add, known_hosts->retrieve(known_hosts, i))==0){
                found = 1;
            }
        }
        if(!found){
            known_hosts->insert (known_hosts, known_hosts->length, client_add, sizeof(client_add));
        }
    }
    return NULL;
}

void client_peer(char *request, struct LinkedList *known_hosts){

    struct Client client = client_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 1248);
    for (int i=0; i<known_hosts->length; i++){
        
        client.request(&client, known_hosts->retrieve(known_hosts, i), request);
    }
}

int main(){
    
    struct LinkedList known_hosts = linked_list_constructor();
    known_hosts.insert(&known_hosts, 0, "127.0.0.1", 10);

    printf("Starting ...\n");
    pthread_t server_thread;
    pthread_create(&server_thread, NULL, server_peer, &known_hosts);

    while(1){
        char request[255];
        memset(request, 0, 255);
        fgets(request, 255, stdin);
        client_peer(request, &known_hosts);
    }
}