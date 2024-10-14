#include "client.h"
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char * request(struct Client *client, char *server_ip, char *request);

struct Client client_constructor(int domain, int service, int protocol, u_long interface, int port){

    struct Client client;
    client.domain = domain;
    client.service = service;
    client.protocol = protocol;
    client.interface = interface;
    client.port = port;

    client.socket = socket(domain, service, protocol);
    client.request = request;

    return client;
}

char * request(struct Client *client, char *server_ip, char *request){

    struct sockaddr_in server_add;

    server_add.sin_family = client->domain;
    server_add.sin_port = htons(client->port);
    server_add.sin_addr.s_addr = (int)client->interface;
    
    inet_pton(client->domain, server_ip, &server_add.sin_addr);
    connect(client->socket, (struct sockaddr*)&server_add, sizeof(server_add));

    send(client->socket, request, sizeof(request), 0);
    char *response = malloc(30000);
    read(client->socket, response, 30000);
    return response;
}