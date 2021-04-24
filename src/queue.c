
/** WARNING: Untested. Don't use this code yet until I go through it. */

/**
 * queue.c - Code definitions for a queue data structure.
 * 
 * Licensed per the terms found in the LICENSE file at the root of this
 * code repository.
 * 
 */

/**
 * QUEUE
 * A queue is a first in, first out (FIFO) data structure, emulating that
 * of a queue line you'd find at a grocery store checkout--the first person
 * in the line will be the first person to be helped by the cashier, etc.
 * 
 * The queue structure implemented here uses a helper data structure
 * that keeps track of the size of the queue, the first element added,
 * and the last element added. A more memory-lean version of a queue could
 * merely use a linked list and nothing else, but this would affect time
 * complexity such that most functions would be O(n) rather than O(1).
 * 
 * TIME COMPLEXITY
 * All aspects of this queue implementation are O(1) at the expense of
 * very, very slightly higher memory usage (on the order of a few bytes
 * extra per element, aka 2 to 3 pointers vs 1 pointer).
 * 
 */

#include <stdlib.h>
#include <queue.h>

struct queue {
    size_t size;
    queue_element_t* firstAdded;
    queue_element_t* lastAdded;
};

struct queue_element {
    queue_element_t* next;
    queue_element_t* prev;
    void* data;
};

/* Safely zeroes the contents of a queue, since malloc()
   doesn't guarantee zero (yes, we could use calloc, but that
   seems like an overengineered approach compared to just...
   y'know, setting a variable) */
void zero_queue(queue_t* q) {
    q->lastAdded = NULL;
    q->size = 0;
}

/* Does the same as above, but for elements, not the queue. */
void zero_element(queue_element_t* el) {
    el->data = NULL;
    el->next = NULL;
    el->prev = NULL;
}

/* Allocates and zeroes out a queue. */
queue_t* queue_create() {
    queue_t* ret = malloc(sizeof(queue_t));
    zero_queue(ret);
    return ret;
}

/* Dequeues the contents of a given queue. */
void queue_clear(queue_t* q) {
    if (q == NULL) return;
    while (q->size > 0)
        dequeue(q);
}

/* Destroys the current queue and its elements */
void queue_destroy(queue_t* q) {
    queue_clear(q);
    free(q);
}

/* Adds the given element to the queue */
void enqueue(queue_t* q, void* data) {
    queue_element_t* el = malloc(sizeof(queue_element_t));
    el->data = data;            /* put the data pointer */
    el->next = q->lastAdded;    /* let the element know what's in front of it */
    if (q->lastAdded != NULL)
        q->lastAdded->prev = el; /* tell former last-in-line about new el */
    q->lastAdded = el;           /* update queue to point to end of line */
    q->size++;
}

/* Returns the least recently added element in the queue */
void* peek(queue_t* q) {
    return q->firstAdded;
}

/* Removes the given element from the queue */
void* dequeue(queue_t* q) {
    queue_element_t* el = q->firstAdded; /* get the least-recently added one */
    void* data;
    if (q->firstAdded == NULL) /* return null early just in case */
        return NULL;
    
    if (el->prev != NULL)
        el->prev->next = NULL; /* tell its successor it's in the front now */
    
    q->firstAdded = el->prev; /* set the new least-recent added element */
    q->size--;
    
    data = el->data;
    free(el);
    return data;
}

/* Returns the size of the queue */
size_t queue_get_size(queue_t* q) {
    return q->size;
}

