#include "network/server.c"
#include "network/client.c"
#include "systems/thread.c"
#include "datastructures/queue.c"
#include "datastructures/linkedlist.c"
#include "datastructures/node.c"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct ServerLoopArg{
    
    int client;
    struct Server *serving;
    struct LinkedList *known_hosts;
};

void * server_loop(void *arg){

    struct ServerLoopArg *server_arg = arg;
    char request[255];
    memset(request, 0, 255);
    read(server_arg->client, request, 255);
    char *client_add = inet_ntoa(server_arg->serving->address.sin_addr);
    printf("\t\t %s says: %s\n", client_add, request);
    close(server_arg->client);
    
    short found = 0;
    for (int i=0; i<server_arg->known_hosts->length&&!found; i++){
        if(strcmp(client_add, server_arg->known_hosts->retrieve(server_arg->known_hosts, i))==0){
                found = 1;
            }
        }
        if(!found){
            server_arg->known_hosts->insert(server_arg->known_hosts, server_arg->known_hosts->length, client_add, sizeof(client_add));
        }
    return NULL;
}

void * server_peer(void *arg){

    //struct LinkedList *known_hosts = arg;

    printf("Starting Peer Server...\n");
    struct Server serving = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 1248, 20 );
    struct sockaddr *address = (struct sockaddr *)&serving.address; 
    struct ThreadPool threadpool = threadpool_constructor(50);
    socklen_t add_len = (socklen_t)sizeof(serving.address);
 
    while(1){
        
        struct ServerLoopArg server_arg;
        server_arg.client= accept(serving.socket, address, &add_len);
        server_arg.serving = &serving;
        server_arg.known_hosts = arg;

        struct ThreadJob threadjob = threadjob_constructor(server_loop, &server_arg);
        threadpool.add_work(&threadpool,threadjob);
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