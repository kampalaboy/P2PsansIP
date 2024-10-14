#ifndef Server_h
#define Server_h

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct Server{
    
    int domain;
    int service;
    int protocol;
    u_long interface;
    int port;
    int backlog;

    struct sockaddr_in address;
    
    int socket;

    void (*launch)(struct Server *serving);
};

struct Server server_constructor(int domain,  int service, int protocol, u_long interface, 
                  int port,  int backlog);

#endif 