
/**
 * queue.h - Header file for all things queue-related
 * 
 * Licensed per the terms found in the LICENSE file at the root of this
 * code repository.
 * 
 */

#ifndef __QUEUE_H
#define __QUEUE_H
#include <stdlib.h>

typedef struct queue_element queue_element_t;
typedef struct queue queue_t;

queue_t* queue_create();
void queue_clear(queue_t* q);
void queue_destroy();
void enqueue(queue_t* q, void* data);
void* peek(queue_t* q);
void* dequeue(queue_t* q);
size_t queue_get_size(queue_t* q);

#endif