
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
 * All aspects of this stack implementation are O(1), unless the host
 * systems malloc/free implementations are anything worse than O(1).
 * 
 * SPACE CONSIDERATIONS
 * Note that this particular implementation of a stack may be prone to
 * heap fragmentation on the host system. While the stack structure will
 * only ever occupy 2 pointers worth (16 bytes on a 64-bit system) of
 * space--same for the elements--the malloc() and free() calls used to
 * set up the space
 * 
 * A stack implementation that uses a resizable array--an approach called
 * an "implicit data structure"--can be seen in impstack.c instead. Gen-
 * erally speaking, the system will just re-use previously allocated stack
 * structures (i.e., if you free a 16-byte block, and later allocate one,
 * most systems are smart enough to know they can just reuse the previously
 * freed block). However, depending on the host system, its use of paging,
 * and pre-existing RAM usage that may lead to swapping/disk thrashing, this
 * may still present an issue.
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
