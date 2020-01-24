/// \brief interface du type queue
/// \brief permettant l'implémentation en statique et en dynamique

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

//  L'utilisateur ne dois pas accéder a la rep interne du type:
//  il faut proteger l'implémentation : mise en place de 'getter' et de 'setter'
// avec un pointeur sur la structure

//  ici, on ne définit uniquement un pointeur sur la structure
//  qui elle sera définit dans le .c, dans l'implémentation

typedef struct s_queue *Queue;

Queue queue();
Queue queue_push(Queue q, int v);
Queue queue_pop(Queue q);
int queue_top(Queue q);
bool queue_empty(Queue q);

#endif