#ifndef CERVER_CALLBACK_QUEUE_H
#define CERVER_CALLBACK_QUEUE_H

#include "./enums.h"

struct CallbackQueueNode {
    void (*handler)(void);
    struct CallbackQueueNode *next;
};

typedef struct CallbackQueueNode CallbackQueueNode;

struct CallbackQueue {
    unsigned int amountOfItems;
    CallbackQueueNode *first;
};

typedef struct CallbackQueue CallbackQueue;

CallbackQueue *CallbackQueue_init();

ReturnType CallbackQueue_add(CallbackQueue *queue, void (*handler)(void));

simple_callback CallbackQueue_removeLast(CallbackQueue *queue);

simple_callback CallbackQueue_getNext(CallbackQueue *queue);

void CallbackQueue_destroy(CallbackQueue *queue);

#endif /* CERVER_CALLBACK_QUEUE_H */
