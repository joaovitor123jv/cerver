#include "./testlib.h"
#include "./globals.h"

#include "../data_utils/callback_queue.h"

char _callback_queue_first_test_flag = '0';
char _callback_queue_second_test_flag = '0';

void _callback_queue_update_first_test_flag()
{
    _callback_queue_first_test_flag = '1';
}

void _callback_queue_update_second_test_flag()
{
    _callback_queue_second_test_flag = '1';
}


void can_create_and_destroy_callback_queues()
{
    start_test("can create CallbackQueue");
    CallbackQueue *queue = CallbackQueue_init();
    ENSURE(queue != NULL);
    ENSURE(queue->amountOfItems == 0);
    ENSURE(queue->first == NULL);
    test_done();

    start_test("can destroy CallbackQueue");
    CallbackQueue_destroy(queue);
    test_done();
}

void can_add_and_remove_from_callback_queue()
{
    /* Test setup */
    void (*handler)() = NULL;
    CallbackQueue *queue = CallbackQueue_init();
    ENSURE(queue != NULL);
    ENSURE(queue->amountOfItems == 0);
    ENSURE(queue->first == NULL);
    /* End test setup */

    start_test("can add one callback to CallbackQueue");
        CallbackQueue_add(queue, _callback_queue_update_first_test_flag);
        ENSURE(queue->amountOfItems == 1);
        ENSURE(queue->first->handler == _callback_queue_update_first_test_flag);
        ENSURE(queue->first->next == NULL);
    test_done();

    start_test("can add two callback to CallbackQueue");
        CallbackQueue_add(queue, _callback_queue_update_second_test_flag);
        ENSURE(queue->amountOfItems == 2);
        ENSURE(queue->first->handler == _callback_queue_update_first_test_flag);
        ENSURE(queue->first->next->handler == _callback_queue_update_second_test_flag);
    test_done();

    start_test("can remove one callback from CallbackQueue");
        ENSURE(handler == NULL);
        handler = CallbackQueue_getNext(queue);
        ENSURE(handler == _callback_queue_update_first_test_flag);
        ENSURE(queue->amountOfItems == 1);
        ENSURE(queue->first->handler == _callback_queue_update_second_test_flag);
    test_done();

    start_test("can use first CallbackQueue return as expected function");
        ENSURE(_callback_queue_first_test_flag == '0');
        handler();
        ENSURE(_callback_queue_first_test_flag == '1');
    test_done();

    start_test("can remove second callback from CallbackQueue");
        handler = NULL;
        ENSURE(handler == NULL);
        handler = CallbackQueue_getNext(queue);
        ENSURE(handler == _callback_queue_update_second_test_flag);
        ENSURE(queue->amountOfItems == 0);
        ENSURE(queue->first == NULL);
    test_done();

    start_test("can use second CallbackQueue return as expected function");
        ENSURE(_callback_queue_second_test_flag == '0');
        handler();
        ENSURE(_callback_queue_second_test_flag == '1');
    test_done();

    start_test("can remove from empty CallbackQueue");
        handler = NULL;
        ENSURE(handler == NULL);
        handler = CallbackQueue_getNext(queue);
        ENSURE(handler == NULL);
        ENSURE(queue->amountOfItems == 0);
        ENSURE(queue->first == NULL);
    test_done();

    CallbackQueue_destroy(queue);
}

void can_destroy_non_empty_CallbackQueue()
{
    start_test("can destroy CallbackQueue with one callback");
        CallbackQueue *queue = CallbackQueue_init();
        ENSURE(queue != NULL);
        ENSURE(queue->amountOfItems == 0);
        ENSURE(queue->first == NULL);

        CallbackQueue_add(queue, _callback_queue_update_first_test_flag);
        ENSURE(queue->amountOfItems == 1);
        ENSURE(queue->first->handler == _callback_queue_update_first_test_flag);
        ENSURE(queue->first->next == NULL);

        CallbackQueue_destroy(queue);
    test_done();

    start_test("can destroy CallbackQueue with two callbacks");
        queue = CallbackQueue_init();
        ENSURE(queue != NULL);
        ENSURE(queue->amountOfItems == 0);
        ENSURE(queue->first == NULL);

        CallbackQueue_add(queue, _callback_queue_update_first_test_flag);
        ENSURE(queue->amountOfItems == 1);
        ENSURE(queue->first->handler == _callback_queue_update_first_test_flag);
        ENSURE(queue->first->next == NULL);

        CallbackQueue_add(queue, _callback_queue_update_second_test_flag);
        ENSURE(queue->amountOfItems == 2);
        ENSURE(queue->first->handler == _callback_queue_update_first_test_flag);
        ENSURE(queue->first->next->handler == _callback_queue_update_second_test_flag);

        CallbackQueue_destroy(queue);
    test_done();
}


void init_callback_queue_tests()
{
    CallbackQueue_add(test_queue, 
            can_create_and_destroy_callback_queues);

    CallbackQueue_add(test_queue, 
            can_add_and_remove_from_callback_queue);

    CallbackQueue_add(test_queue,
            can_destroy_non_empty_CallbackQueue);
}
