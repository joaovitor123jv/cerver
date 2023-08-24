#ifndef CERVER_ENDPOINT_TREE
#define CERVER_ENDPOINT_TREE

#include "../data_utils/enums.h"
#include "./http_request.h"

struct EndpointTree {
    char *path;
    void (*get_handler)(void);
    void (*patch_handler)(void);
    void (*put_handler)(void);
    void (*delete_handler)(void);
    void (*post_handler)(void);
    void (*options_handler)(void);
    void (*head_handler)(void);
    void (*connect_handler)(void);
    void (*trace_handler)(void);
    struct EndpointTree **childs;
    unsigned int amount_of_childs;
};

typedef struct EndpointTree EndpointTree;

EndpointTree *EndpointTree_init();


void EndpointTree_addRoute(EndpointTree *tree, char *path, HttpMethod method, void (*handler)(void));
simple_callback EndpointTree_getHandler(EndpointTree *tree, HttpRequest *request);

#endif /* CERVER_ENDPOINT_TREE */
