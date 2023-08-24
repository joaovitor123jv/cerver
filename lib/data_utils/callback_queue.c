#include<stdlib.h>
#include<stdio.h>

#include "./callback_queue.h"
#include "./enums.h"

CallbackQueue *CallbackQueue_init()
{
    CallbackQueue *queue = (CallbackQueue *)malloc(sizeof(CallbackQueue));
    if(queue == NULL)
    {
        fprintf(stderr, "Failed to mallot for CallbackQueue\n");
        return NULL;
    }
    queue->amountOfItems = 0;
    queue->first = NULL;

    return queue;
}

CallbackQueueNode *CallbackQueueNode_create(void (*handler)())
{
    CallbackQueueNode *node = NULL;
    if(handler == NULL)
    {
        fprintf(stderr, "Handler cannot be NULL in CallbackQueueNode_add\n");
        return NULL;
    }

    node = (CallbackQueueNode *)malloc(sizeof(CallbackQueueNode));
    if(node == NULL)
    {
        fprintf(stderr, "Cannot mallot in CallbackQueueNode_create\n");
        return NULL;
    }

    node->handler = handler;
    node->next = NULL;

    return node;
}

ReturnType CallbackQueue_add(CallbackQueue *queue, void (*handler)(void))
{
    CallbackQueueNode *tempNode = NULL;
    if(queue == NULL)
    {
        fprintf(stderr, "Cannot add to CallbackQueue NULL");
        return ERROR;
    }

    if(queue->first == NULL)
    {
        queue->first = CallbackQueueNode_create(handler);
        if(queue->first == NULL) return ERROR;
        queue->amountOfItems++;
        return OK;
    }

    tempNode = queue->first;

    while(tempNode->next != NULL)
    {
        tempNode = tempNode->next;
    }

    tempNode->next = CallbackQueueNode_create(handler);
    if(tempNode->next == NULL) return ERROR;
    queue->amountOfItems++;
    return OK;
}


simple_callback CallbackQueue_returnLast(CallbackQueue *queue)
{
    CallbackQueueNode *tempNode = NULL;
    CallbackQueueNode *previousNode = NULL;
    void (*handler)(void) = NULL;

    if(queue == NULL)
    {
        fprintf(stderr, "Cannot remove last from NULL CallbackQueue\n");
        return NULL;
    }

    if(queue->amountOfItems == 0)
    {
        fprintf(stderr, "Cannot remove last from empty CallbackQueue\n");
        return NULL;
    }

    if(queue->amountOfItems == 1)
    {
        tempNode = queue->first;
        queue->first = NULL;
        handler = tempNode->handler;
        free(tempNode);
        tempNode = NULL;
        queue->amountOfItems--;
        return handler;
    }

    tempNode = queue->first;

    while(tempNode->next != NULL)
    {
        previousNode = tempNode;
        tempNode = tempNode->next;
    }

    previousNode->next = NULL;
    handler = tempNode->handler;
    free(tempNode);
    tempNode = NULL;
    queue->amountOfItems--;
    return handler;
}

simple_callback CallbackQueue_getNext(CallbackQueue *queue)
{
    CallbackQueueNode *node = NULL;
    void (*handler)(void) = NULL;

    if(queue == NULL)
    {
        fprintf(stderr, "Cannot get next from NULL CallbackQueue\n");
        return NULL;
    }
    if(queue->amountOfItems == 0)
    {
        return NULL;
    }
    if(queue->amountOfItems == 1)
    {
        node = queue->first;
        handler = node->handler;
        queue->first = NULL;
        free(node);
        node = NULL;
        queue->amountOfItems = 0;
        return handler;
    }

    node = queue->first;
    queue->first = queue->first->next;
    handler = node->handler;
    free(node);
    node = NULL;
    queue->amountOfItems--;
    return handler;
}

void CallbackQueue_destroy(CallbackQueue *queue)
{
    if(queue == NULL) return;
    while(queue->amountOfItems != 0)
    {
        CallbackQueue_getNext(queue);
    }

    free(queue);
    queue = NULL;
}

