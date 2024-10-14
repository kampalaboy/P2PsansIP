#include "server.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

struct Server server_constructor(int domain, int service,  int protocol, 
                    u_long interface, int port, int backlog)
{
    
    struct Server serving;

    serving.domain = domain;
    serving.service = service;
    serving.protocol = protocol;
    serving.interface = interface;
    serving.port = port;
    serving.backlog = backlog;

    serving.address.sin_family = domain;
    serving.address.sin_port = htons(port);
    serving.address.sin_addr.s_addr = htonl(interface);

    serving.socket = socket(domain, service, protocol);
    if(serving.socket == 0){
        perror("Failed to initialize socket!\n");
        exit(1);
    }
   if(bind(serving.socket,(struct sockaddr *)&serving.address, sizeof(serving.address)) < 0){
        perror("Failed to bind to network!\n");
        exit(1);
   }
   if(listen(serving.socket, serving.backlog) < 0){
        perror("Failed to start listening!\n");
        exit(1);
   }

//    serving.launch =launch;
    return serving;
}

