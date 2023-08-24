#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../data_utils/callback_queue.h"
#include "./globals.h"
#include "./testlib.h"

#include "./http_request_tests.h"
#include "./callback_queue_tests.h"


int main()
{
    void (*handler)() = NULL;
    printf("Configuring tests...\n");
    test_queue = CallbackQueue_init();

    init_callback_queue_tests();
    init_http_request_tests();

    printf("Running tests...\n");

    handler = CallbackQueue_getNext(test_queue);

    while(handler != NULL)
    {
        handler();
        handler = CallbackQueue_getNext(test_queue);
    }
    
    CallbackQueue_destroy(test_queue);
    print_results();
}
