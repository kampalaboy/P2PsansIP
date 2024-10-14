#ifndef httprequest_h
#define httprequest_h

enum HttpMethods{
    GET,
    POST,
    PUT,
    HEAD,
    PATCH,
    DELETE,
    OPTIONS,
    TRACE
};

struct HttpRequest{
    int Method;
    char *URI;
    float HttpVersion;
};

struct HttpRequest httprequest_constructor(char *requester);

#endif