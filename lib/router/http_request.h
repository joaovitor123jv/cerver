#ifndef CERVER_HTTP_REQUEST_H
#define CERVER_HTTP_REQUEST_H

#include "../data_utils/hashmap.h"

enum HttpMethod {
    GET,
    PUT,
    PATCH,
    POST,
    DELETE,
    OPTIONS,
    HEAD,
    CONNECT,
    TRACE
};

typedef enum HttpMethod HttpMethod;

struct HttpRequest {
    const char* path;
    HttpMethod method;
    HashMap *headers;
};

typedef struct HttpRequest HttpRequest;

HttpRequest *HttpRequest_init(const char* const path, HttpMethod method);
void HttpRequest_destroy(HttpRequest *request);

void HttpRequest_addHeader(HttpRequest *request, char *key, char *value);
void HttpRequest_rmHeader(HttpRequest *request, char *key);
char *HttpRequest_getHeader(HttpRequest *request, char *key);


#endif /* CERVER_HTTP_REQUEST_H */
