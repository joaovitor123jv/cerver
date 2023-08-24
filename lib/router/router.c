#include <stdio.h>
#include <stdlib.h>

#include "./router.h"

CerverRouter *CerverRouter_init()
{
    CerverRouter *router = (CerverRouter *)malloc(sizeof(CerverRouter));
    if (router == NULL)
    {
        fprintf(stderr, "Error: malloc failed in CerverRouter_init\n");
        exit(1);
    }

    router->routes = EndpointTree_init();
    router->received_requests = 0;
    router->responded_requests = 0;
    return router;
}

void CerverRouter_addRoute(CerverRouter *router, char *path, HttpMethod method, void (*handler)(void))
{
    if(router == NULL)
    {
        fprintf(stderr, "Error: router is NULL in CerverRouter_addRoute\n");
        exit(1);
    }
    
    EndpointTree_addRoute(router->routes, path, method, handler);
}

void CerverRouter_respond(CerverRouter *router, HttpRequest *request)
{
    if(router == NULL)
    {
        fprintf(stderr, "Error: router is NULL in CerverRouter_respond\n");
        exit(1);
    }
    
    void (*handler)(void) = EndpointTree_getHandler(router->routes, request);
        if(handler == NULL)
    {
        fprintf(stderr, "Error: handler is NULL in CerverRouter_respond\n");
        exit(1);
    }
    (handler)();
}
