#ifndef CERVER_H
#define CERVER_H

#include "./router/router.h"

struct Cerver {
    int port;
    int socket;
    CerverRouter *router;
};

typedef struct Cerver Cerver;

Cerver *Cerver_init(int port);

void Cerver_start(Cerver *cerver);

void Cerver_destroy(Cerver *cerver);

#endif
