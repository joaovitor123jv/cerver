#include<stdio.h>
#include<stdlib.h>

#include "./endpoint_tree.h"

EndpointTree *EndpointTree_init()
{
    EndpointTree *tree = (EndpointTree *)malloc(sizeof(EndpointTree));
    if(tree == NULL)
    {
        printf("EndpointTree_init: malloc failed\n");
        exit(1);
    }

    tree->path = "/";
    tree->childs = NULL;
    tree->amount_of_childs = 0;

    return tree;
}

void EndpointTree_setHandler(EndpointTree *tree, HttpMethod method, void (*handler)(void))
{
    switch(method)
    {
        case GET:
            tree->get_handler = handler;
            break;
        case POST:
            tree->post_handler = handler;
            break;
        case PUT:
            tree->put_handler = handler;
            break;
        case DELETE:
            tree->delete_handler = handler;
            break;
        case PATCH:
            tree->patch_handler = handler;
            break;
        case HEAD:
            tree->head_handler = handler;
            break;
        case OPTIONS:
            tree->options_handler = handler;
            break;
        case CONNECT:
            tree->connect_handler = handler;
            break;
        case TRACE:
            tree->trace_handler = handler;
            break;
        default:
            printf("EndpointTree_setHandler: unknown method\n");
            exit(1);
    }
}

void EndpointTree_addRoute(EndpointTree *tree, char *path, HttpMethod method, void (*handler)(void))
{
    if(tree == NULL)
    {   
        printf("EndpointTree_addRoute: tree is NULL\n");
        exit(1);
    }

    if(path == NULL)
    {
        printf("EndpointTree_addRoute: path is NULL\n");
        exit(1);
    }

    if(handler == NULL)
    {
        printf("EndpointTree_addRoute: handler is NULL\n");
        exit(1);
    }

    if(path[0] == '/' && path[1] == '\0')
    {
        EndpointTree_setHandler(tree, method, handler);
        return;
    }
}

simple_callback EndpointTree_getHandler(EndpointTree *tree, HttpRequest *request)
{
    if(tree == NULL)
    {
        printf("EndpointTree_getHandler: tree is NULL\n");
        exit(1);
    }
    if(request == NULL)
    {
        printf("EndpointTree_getHandler: request is NULL\n");
        exit(1);
    }

    if(request->path[0] == '/' && request->path[1] == '\0')
    {
        switch(request->method)
        {
            case GET:
                return tree->get_handler;
            case POST:
                return tree->post_handler;
            case PUT:
                return tree->put_handler;
            case DELETE:
                return tree->delete_handler;
            case PATCH:
                return tree->patch_handler;
            case HEAD:
                return tree->head_handler;
            case OPTIONS:
                return tree->options_handler;
            case CONNECT:
                return tree->connect_handler;
            case TRACE:
                return tree->trace_handler;
            default:
                printf("EndpointTree_getHandler: unknown method\n");
                exit(1);
        }
    }
    else
    {
        return NULL;
    }
}

