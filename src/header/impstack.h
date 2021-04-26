
/**
 * impstack.h - Header file for all things array-backed-stack-related
 * 
 * Licensed per the terms found in the LICENSE file at the root of this
 * code repository.
 * 
 */

#ifndef __IMPSTACK_H
#define __IMPSTACK_H
#include <stddef.h>

typedef struct istack istack_t;

istack_t* impstack_create();
void impstack_clear(istack_t* stack);
void impstack_destroy(istack_t* stack);
void impstack_push(istack_t* stack, void* data);
void* impstack_pop(istack_t* stack);
size_t impstack_get_size(istack_t* stack);
#endif