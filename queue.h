#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __QUEUE__
#define __QUEUE__

#define DATA_SIZE 12

typedef struct _QueueNode {
    char data[DATA_SIZE + 1];
    int isDone;
    struct _QueueNode *next;
    struct _QueueNode *prev;
} QueueNode, *pQueueNode;

typedef struct _Queue {
    pQueueNode top;
    pQueueNode tail;
    int size;
} Queue, *pQueue;

pQueue createQueue();

int enQueue(pQueue q, char data[]);

pQueueNode deQueue(pQueue q);

int size(pQueue q);

int isEmpty(pQueue q);

int printQueue(pQueue q);

int freeQueue(pQueue q);

#endif
