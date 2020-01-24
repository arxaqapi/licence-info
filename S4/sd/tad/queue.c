/// \brief implémentation du type queue
#include "queue.h"

// 'CIRCULAIRE'

#define QUEUE_SIZE_MAX 32

struct s_queue
{
    int queue[QUEUE_SIZE_MAX];
    int head;
    int tail;
    unsigned int size;
};

Queue queue()
{
    Queue q = (Queue)malloc(sizeof(struct s_queue));
    q->size = 0;
    q->head = 0;
    q->tail = -1;
    return q;
}

Queue queue_push(Queue q, int v)
{
    assert(q->size < QUEUE_SIZE_MAX);
    q->queue[q->tail] = v;
    q->tail = (q->tail + 1) % QUEUE_SIZE_MAX;
    q->size ++;
    return q;
}

Queue queue_pop(Queue q)
{
    assert(!queue_empty(q));
    q->head = (q->head + 1) % QUEUE_SIZE_MAX;
    return q;
}

int queue_top(Queue q)
{
    assert(!queue_empty(q));
    return q->queue[q->head];
}

bool queue_empty(Queue q)
{
    return q->size == 0;
}