
/**
 * stack.h - Header file for all things stack-related
 * 
 * Licensed per the terms found in the LICENSE file at the root of this
 * code repository.
 * 
 */

#ifndef __STACK_H
#define __STACK_H
#include <stdlib.h>

typedef struct stack stack_t;

stack_t* stack_create();
void stack_clear(stack_t* stack);
void stack_destroy(stack_t* stack);
void stack_push(stack_t* stack, void* data);
void* stack_pop(stack_t* stack);
size_t stack_get_size(stack_t* stack);
#endif