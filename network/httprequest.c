#include "httprequest.h"
#include <string.h>

    int method_select(char *method){

        if (strcmp(method, "GET")==0){
            return GET;
        }else if (strcmp(method, "POST")==0){
            return POST;
        }else if (strcmp(method, "PUT")==0){
            return PUT;
        }else if (strcmp(method, "HEAD")==0){
            return HEAD;
        }else if (strcmp(method, "PATCH")==0){
            return PATCH;
        }else if (strcmp(method, "DELETE")==0){
            return DELETE;
        }else if (strcmp(method, "OPTIONS")==0){
            return OPTIONS;
        }else if (strcmp(method, "TRACE")==0){
            return TRACE;
        }
        
    }
 
struct HttpRequest httprequest_constructor(char *requester){

    for (int i=0; i< strlen(requester); i++ ){

        if (requester[i]=="\n" && requester[i+1]){
            requester[i+1] = "|";
        }

    }

    char *request_func = strtok(requester, "/n");
    char *method =strtok(request_func, " ");
    char *headers = strtok(NULL, "|");
    char *body = strtok(NULL, "|");
    char *uri = strtok(NULL, " ");
  
    struct HttpRequest request;

    request.Method =method_select(method);
    request.URI = uri;

    return request;
}