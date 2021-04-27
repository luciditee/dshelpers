
/**
 * vector.h - Header file for all things vector-related
 * 
 * Licensed per the terms found in the LICENSE file at the root of this
 * code repository.
 * 
 */

#ifndef __VECTOR_H
#define __VECTOR_H
#include <stddef.h>

/* C89 does not guarantee stdbool.h */
#define bool int
#define true 1
#define false 0

typedef union vector vector_t;

/* Creates a vector object in memory to be used with these functions */
vector_t* vector_create();

/* Frees memory associated with the vector, but does not free the underlying
   data that was pointed to--that's up to you */
void vector_destroy(vector_t* vector);

/* Performs the same operation as vector_destroy, and creates a new one 
   in its place */
void vector_clear(vector_t* vector);

/* Adds a number of elements to the vector from a given array. */
void vector_append(vector_t* vector, void** data, size_t length);

/* Adds a number of elements to the vector from the given array,
   shifting existing elements ahead in the vector */
void vector_insert(vector_t* vector, void** data, size_t length, size_t index);

/* Removes N elements, starting from startIndex, and shifts remaining
   elements backwards to fill the gap. */
void vector_remove(vector_t* vector, size_t startIndex, size_t count);

/* Removes N elements off the end of the vector. */
void vector_truncate(vector_t* vector, size_t length);

/* Returns the index of the given pointer, or -1 if not found. */
int vector_indexof(vector_t* vector, void* data);

/* Does this vector contain the specified pointer? */
bool vector_contains(vector_t* vector, void** data);

/* Does this vector contain the specified sequence? */
bool vector_contains_string(vector_t* vector, void** data, size_t length);

/* Returns the size of the specified vector (its number of elements). */
size_t vector_sizeof(vector_t* vector);

/* Coerces the vector to an array. You probably don't need this because
   vector objects have a pointer to their associated memory, just like
   a heap array, as the first component of the object. Thus, in most
   cases, you can just pass the vector directly and it should work. 
   This is mainly for cases where type strictness gets in the way */
void** vector_toarray(vector_t* vector);

#endif