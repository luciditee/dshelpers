
/** WARNING: Untested. Don't use this code yet until I go through it. */

/**
 * stack.c - Code definitions for a stack data structure.
 * 
 * Licensed per the terms found in the LICENSE file at the root of this
 * code repository.
 * 
 */

/**
 * STACK
 * (Same as stack.c)
 * A stack is a FILO (first in, last out) data structure in which elements
 * are appended, and when un-appended, the most recently added element is
 * removed, similar to a stack of papers on a desk--placing new papers on
 * top means that the next paper you grab will always be the most recently
 * added paper in the stack of papers.
 * 
 * The act of putting something on the stack is called 'pushing', and the
 * removal is called 'popping'.
 * 
 * The stack implemented here uses a helper data structure that also allows
 * us to summon the *size* of the stack at any one time, as well as a stack
 * element structure that contains a pointer to the previous element.
 * 
 * A typical use case for a stack would be an *undo* feature. Combining this
 * stack with a queue structure would facilitate an accompanying *redo*
 * feature.
 * 
 * TIME COMPLEXITY
 * Most functions are O(1). However, when the size of the stack is maxed out,
 * the underlying array is resized and copied, which is O(n). A downsize occurs
 * when the number of active elements in the stack drops below half the size
 * of the next-lowest size multiple, which is also O(n).
 * 
 * This avoids heap fragmentation as with the other stack implementation, but
 * the expense is time. If time is the constraint, not space--use stack.c.
 * 
 * SPACE CONSIDERATIONS
 * This is an implicit stack, which means it uses an array as the underlying
 * structure rather than fragmented mallocs() for each stack element.
 * 
 */

#include <stdlib.h>
#include <string.h>
#include <impstack.h>

#define SIZE_MULT 64
#define bool int
#define true 1
#define false 0

struct istack {
    size_t size;
    size_t current;
    void** array;
};

istack_t* impstack_create() {
    istack_t* stack = malloc(sizeof(istack_t));
    stack->array = NULL;
    impstack_clear(stack); /* Freeing a null pointer is a no-op */
    return stack;
}

void impstack_clear(istack_t* stack) {
    int i;

    free(stack->array);
    stack->array = malloc(sizeof(void**)*SIZE_MULT);
    for (i = 0; i < SIZE_MULT; i++) 
        stack->array[i] = NULL;
    
    stack->size = 1;
    stack->current = 0;
}

void impstack_destroy(istack_t* stack) {
    free(stack->array);
    free(stack);
}

void impstack_resize(istack_t* stack, bool sizeInc) {
    void** newArray = malloc(sizeof(void**)
        * SIZE_MULT*(sizeInc ? stack->size+1 
            : stack->size-1));
    memcpy(newArray, stack->array, stack->size * SIZE_MULT);
    free(stack->array);
    stack->array = newArray;
    stack->size++;
}

void impstack_push(istack_t* stack, void* data) {
    /* Resize the array if applicable */
    if (++(stack->current) >= (stack->size * SIZE_MULT)) 
        impstack_resize(stack, true);
    
    /* At this point the current val should point to the index
       we can safely store data at */
    stack->array[stack->current] = data;
}

void* impstack_pop(istack_t* stack) {
    void* ret = stack->array[stack->current];

    if (stack->current > 0)
        stack->current--;
    
    if (stack->size > 1 && stack->current < ((stack->size-1) * SIZE_MULT)) 
        impstack_resize(stack, false);

    return ret;
}

void* impstack_peek(istack_t* stack) {
    return stack->array[stack->current];
}

size_t impstack_get_size(istack_t* stack) {
    return stack->current;
}