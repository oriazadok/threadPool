#include "queue.h"

pQueue createQueue() {
    pQueue q = (pQueue)malloc(sizeof(Queue));
    q->top = NULL;
    q->tail = NULL;
    q->size = 0;

    return q;
}

int enQueue(pQueue q, char data[]) {
    pQueueNode node = (pQueueNode)malloc(sizeof(QueueNode));
    strncpy(node->data, data, DATA_SIZE);
    node->data[DATA_SIZE] = '\0';
    node->isDone = 0;
    node->next = NULL;
    node->prev = NULL;

    if( ! q->top ) {
        q->top = node;
        q->tail = node;
        q->size++;

        return 0;
    }

    node->next = q->tail;
    q->tail->prev = node;
    q->tail = node;
    q->size++;

    return 0;
}

pQueueNode deQueue(pQueue q) {

    if(q->size == 0) {
        // printf("queue is empty!\n");
        return NULL;
    }

    pQueueNode rm = q->top;

    if(q->size == 1) {
        q->top = NULL;
        q->tail = NULL;
        q->size--;

        return rm;
    }


    q->top = q->top->prev;
    q->top->next = NULL;
    q->size--;
    return rm;
}

int size(pQueue q) {
    return q->size;
}

int isEmpty(pQueue q) {
    if(q->size == 0) {
        return 1;
    }
    return 0;
}

int printQueue(pQueue q) {

    // pQueueNode curr = q->tail;

    // while( curr ) {
    //     for(int i = 0; i < DATA_SIZE; i++) {
    //         printf("%c", curr->data[i]);
    //     }
    //     if(curr->next) {
    //         printf(" -> ");
    //     }
    //     curr = curr->next;
    // }

    pQueueNode curr = q->top;

    while( curr ) {
        for(int i = 0; i < DATA_SIZE; i++) {
            printf("%c", curr->data[i]);
        }
        if(curr->prev) {
            printf(" -> ");
        }
        curr = curr->prev;
    }

    printf("\nend of queue\n");

    return 0;
}

int freeQueue(pQueue q) {
    pQueueNode del = NULL;

    while( q->top ) {
        del = q->top;
        q->top = q->top->prev;
        free(del);
    }

    free(q);

    return 0;
}