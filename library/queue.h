#ifndef QUEUE_H
#define QUEUE_H

#include "node.h"

typedef struct queue *Queue;
struct queue {
    Celula head;
    int size;
};

void queueInit();
void pushQueue(Node v);
Node popQueue();
int emptyQueue();


#endif
