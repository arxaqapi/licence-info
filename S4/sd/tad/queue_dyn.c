#include "queue.h"

//  une cellule pour un élément
typedef struct s_internal_queue
{
    int value;
    struct s_internal_queue *next;
} * Internal_queue;

struct s_queue
{
    Internal_queue head;
    Internal_queue tail;
    unsigned int size;
};

//  cond?(if):else;

Queue queue()
{
    Queue q = (Queue)malloc(sizeof(struct s_queue));
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

Queue queue_push(Queue q, int v)
{
    // parceque def d'internal queue est un pointeur
    // Sinon il aurait fallu un pointeur de pointeur
    Internal_queue *insert_at = (q->size? &(q->tail->next): q->head);
    Internal_queue new = (Internal_queue)malloc(sizeof(Internal_queue));
    new->value = v;
    new->next = NULL;
    insert_at = new;
    q->tail = new;
    ++(q->size);    // ???
    return q;
}


Queue queue_pop(Queue q)
{
    assert(!queue_empty(q));
    Internal_queue *old = q->head;
    q->head = q->head->next;
    q->size--;
    free(old);
    return q;
}

int queue_top(Queue q)
{
    assert(!queue_empty(q));
    return q->head->value;
}

bool queue_empty(Queue q)
{
    return (q->size == 0);
}