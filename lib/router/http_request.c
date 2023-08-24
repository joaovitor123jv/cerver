#include "stdio.h"
#include "stdlib.h"

#include "http_request.h"

HttpRequest *HttpRequest_init(const char* const path, HttpMethod method)
{
    if(path == NULL)
    {
        fprintf(stderr, "Error: Path cannot be NULL\n");
        return NULL;
    }

    HttpRequest *request = malloc(sizeof(HttpRequest));
    if(request == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for HttpRequest\n");
        return NULL;
    }

    request->path = path;
    request->method = method;
    request->headers = HashMap_init();
    if(request->headers == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for HttpRequest headers\n");
        return NULL;
    }

    return request;
}

void HttpRequest_destroy(HttpRequest *request)
{
    if(request == NULL)
    {
        fprintf(stderr, "Error: Cannot free NULL HttpRequest\n");
        return;
    }

    if(request->headers != NULL)
    {
        HashMap_destroy(request->headers);
        request->headers = NULL;
    }

    if(request->path != NULL)
    {
        /* This dont need free because it is const char*  */
        request->path = NULL;
    }

    free(request);
}
