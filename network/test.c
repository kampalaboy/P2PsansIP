#include "server.h"
#include <stdio.h>
#include <unistd.h>

void launch(struct Server *serving){
    char buffer[30000];
    int add_len = sizeof(serving->address);
    int new_socket;
    while (1){

    new_socket = accept(serving->socket, (struct sockaddr *)&serving->address, (socklen_t *)&add_len);
    
    read(new_socket, buffer, 30000);
    printf("%s\n", buffer);
    write(new_socket, "<html><body><h1>!Connected to HTTP!</h1></body></html>", 54);
    close(new_socket);
    }
}

int main(){
    struct Server serving = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 10);
    serving.launch(&serving);
}