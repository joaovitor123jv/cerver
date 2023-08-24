#include <stdio.h>
#include <stdlib.h>
#include "./cerver.h"

Cerver *Cerver_init(int port)
{
    Cerver *cerver = (Cerver *)malloc(sizeof(Cerver));
    if(cerver == NULL)
    {
        fprintf(stderr, "Error: malloc failed in Cerver_init\n");
        exit(1);
    }
    cerver->port = port;
    cerver->router = CerverRouter_init();
    return cerver;
}

void Cerver_start(Cerver *cerver)
{
    printf("Starting cerver on port %d\n", cerver->port);
    printf("Imagine que aqui está funcionando 100%%\n");
}

void Cerver_destroy(Cerver *cerver)
{
    if(cerver != NULL)
    {
        free(cerver);
        cerver = NULL;
    }
}
