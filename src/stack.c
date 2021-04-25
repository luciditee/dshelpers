
/** WARNING: Untested. Don't use this code yet until I go through it. */

/**
 * queue.c - Code definitions for a queue data structure.
 * 
 * Licensed per the terms found in the LICENSE file at the root of this
 * code repository.
 * 
 */

#include <stdlib.h>
#include <stack.h>

typedef struct stack_element stack_element_t;

struct stack {
    stack_element_t* last;
    size_t count;
};

struct stack_element {
    stack_element_t* previous;
    void* data;
};

/* Sets the contents of a stack object to be zero,
   so that we have known defaults */
void zero_stack(stack_t* stack) {
    stack->last = NULL;
    stack->count = 0;
}

/* Allocates and zeroes out a stack object, and returns it */
stack_t* stack_create() {
    stack_t* ret = malloc(sizeof(stack_t));
    zero_stack(ret);
    return ret;
}

/* Clears the contents of a stack by popping its contents until
   no contents remain */
void stack_clear(stack_t* stack) {
    if (stack != NULL)
        while (stack->count > 0)
            stack_pop(stack);
}

/* Clears the contents of a stack and then deletes it */
void stack_destroy(stack_t* stack) {
    stack_clear(stack);
    free(stack);
}

/*  Adds an element to the stack. */
void stack_push(stack_t* stack, void* data) {
    stack_element_t* el = malloc(sizeof(stack_element_t));
    el->previous =  stack->last;
    stack->count++;
    stack->last = el;
}

/* Removes (and returns) the last element added to the stack. */
void* stack_pop(stack_t* stack) {
    stack_element_t* last = stack->last;
    void* data;
    if (last == NULL) return NULL;

    stack->last = stack->last->previous;
    stack->count--;
    data = last->data;
    free(last);
    return data;
}

/* Returns the number of elements on the stack. */
size_t stack_get_size(stack_t* stack) {
    return stack->count;
}
