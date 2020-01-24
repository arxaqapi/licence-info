#include "queue.h"

//  une cellule pour un élément
typedef struct s_internal_queue
{
    int value;
    struct s_internal_queue *next;
} *Internal_queue;

struct s_queue {
    Internal_queue head;
    Internal_queue tail;
    unsigned int size;
};


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
    Internal_queue *insert_out = (q->size?&(q->));
    Internal_queue new = (Internal_queue)malloc(sizeof(struct s_internal_queue));
    new->next = NULL;
    new->next = v;
    *insert_out = new;
}