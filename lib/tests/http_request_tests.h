#include "./testlib.h"
#include "./globals.h"

#include "../router/http_request.h"


void can_create_and_destroy_http_request()
{
    HttpRequest *request = NULL;

    start_test("can create HttpRequest");
        ENSURE(request == NULL);
        request = HttpRequest_init("/", GET);
        ENSURE(request != NULL);
        ENSURE(request->path != NULL);
        ENSURE(strcmp(request->path, "/") == 0);
        ENSURE(request->method == GET);
        ENSURE(request->headers != NULL);
    test_done();

    start_test("can destroy HttpRequest");
        HttpRequest_destroy(request);
    test_done();
}


void init_http_request_tests()
{
    CallbackQueue_add(test_queue, can_create_and_destroy_http_request);
}
