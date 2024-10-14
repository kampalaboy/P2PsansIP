#ifndef Client_h
#define Client_h

#include <sys/socket.h>
#include <netinet/in.h>

struct  Client{

    int socket;
    
    int domain;
    int service;
    int protocol;
    u_long interface;
    int port;

    char * (*request)(struct Client *client, char *server_ip, void *request);
};

struct Client client_constructor(int domaian, int service, int protocol, u_long interface,
                                int port);
#endif