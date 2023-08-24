#ifndef CERVER_ROUTER_H
#define CERVER_ROUTER_H

#include "./endpoint_tree.h"


struct CerverRouter {
    EndpointTree *routes;
    unsigned int received_requests;
    unsigned int responded_requests;
};

typedef struct CerverRouter CerverRouter;

CerverRouter *CerverRouter_init();

void CerverRouter_addRoute(CerverRouter *router, char *path, HttpMethod method, void (*handler)(void));

void CerverRouter_respond(CerverRouter *router, HttpRequest *request);

#endif /* CERVER_ROUTER_H */
