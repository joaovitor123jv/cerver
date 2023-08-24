#ifndef CERVER_HTTP_RESPONSE_H
#define CERVER_HTTP_RESPONSE_H

#include "../data_utils/hashmap.h"

enum HttpStatusCodes
{
    HTTP_STATUS_OK = 200,
    HTTP_STATUS_BAD_REQUEST = 400,
    HTTP_STATUS_NOT_FOUND = 404,
    HTTP_STATUS_INTERNAL_SERVER_ERROR = 500
};

typedef enum HttpStatusCodes HttpStatusCodes;

struct HttpResponse
{
    HttpStatusCodes status_code;
    char *body;
    HashMap *headers; /* use like HashMap<std::string, std::string> */
};

typedef struct HttpResponse HttpResponse;


#endif /* CERVER_HTTP_RESPONSE_H */
