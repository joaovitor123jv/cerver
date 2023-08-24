#ifndef CERVER_CLIENT_H
#define CERVER_CLIENT_H

struct Client {
    int port;
    int socket;
    char *name;
    char *ip;
};

typedef struct Client Client;

#endif /* CERVER_CLIENT_H */
