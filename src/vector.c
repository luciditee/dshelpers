/** WARNING: Untested. Don't use this code yet until I go through it. */

/**
 * vector.c - Code definitions for a vector data structure.
 * 
 * Licensed per the terms found in the LICENSE file at the root of this
 * code repository.
 * 
 */

#include <vector.h>
#include <string.h>

#define ARRAY_SIZE 128

typedef struct ivector {
    void** array;
    size_t size;
    size_t internalSize;
} ivector_t;

union vector {
    void** array;
    ivector_t vector;
};

vector_t* vector_create() {
    int i;
    vector_t* ret = malloc(sizeof(vector_t));
    ret->array = malloc(sizeof(void*) * ARRAY_SIZE);
    ret->vector.internalSize = ARRAY_SIZE;
    for (i = 0; i < ret->vector.internalSize; i++)  
        ret->array[i] = NULL;
    ret->vector.size = 0;
    return ret;
}

void vector_destroy(vector_t* vector) {
    free(vector->array);
    free(vector);
}

void vector_clear(vector_t* vector) {
    vector_destroy(vector);
    vector = vector_create();
}

void vector_resize(vector_t* vector, size_t newInternalSize, bool upsize) {
    void* data = vector->array;
    size_t currSize = vector->vector.size;
    void* resizedData = malloc(sizeof(void*) * newInternalSize);
    memcpy(resizedData, data, upsize ? currSize : newInternalSize);
    free(data);

    vector->array = resizedData;
    vector->vector.internalSize = newInternalSize;
    
}

void vector_append(vector_t* vector, void** data, size_t length) {
    unsigned int i, j;
    if (vector->vector.internalSize < (vector->vector.internalSize + length))
        vector_resize(vector, (vector->vector.internalSize + length)
         / ARRAY_SIZE, true);
    
    for (i = vector->vector.size, j = 0; i < (length + vector->vector.size); i++, j++)
        vector->array[i] = data[j];
}

void vector_insert(vector_t* vector, void** data, size_t length, size_t index) {
    unsigned int i, j;
    if (index >= vector->vector.size)
        return vector_append(vector, data, length);

    if (vector->vector.internalSize < (vector->vector.internalSize + length))
        vector_resize(vector, (vector->vector.internalSize + length)
         / ARRAY_SIZE, true);

    /* Copy end-to-beginning, because memory regions may overlap */
    i = (index + length);
    j = index;
    for  (; i >= index; i--, j--)
        vector->array[i] = vector->array[j];
    
    /* Finally, insert the data. */
    for (i = index, j = 0; i < index+length; i++, j++)
        vector->array[i] = data[j];

    vector->vector.size += length;
}

/* Removes the specified number of elements from the vector, starting from
   the given index, and shifts remaining array elements downwards to
   compensate for the difference. */
void vector_remove(vector_t* vector, size_t startIndex, size_t count) {
    int i = startIndex, offset = startIndex + count;
    int oldIdealSize = (vector->vector.size / ARRAY_SIZE) + 1;
    int newIdealSize = ((vector->vector.size - count) / ARRAY_SIZE) + 1;

    for (; i < (startIndex + count); i++, offset++)
        vector->array[i] = vector->array[offset];
    
    // Downsize if required
    if (newIdealSize < oldIdealSize)
        vector_resize(vector, vector->vector.internalSize - ARRAY_SIZE, count);
}

void vector_truncate(vector_t* vector, size_t length) {
    vector->vector.size = length;
}

int vector_indexof(vector_t* vector, void* data) {
    int i;
    for (i = 0; i < vector->vector.size; i++)
        if (vector->array[i] == data)
            return i;
    return -1;
}

bool vector_contains(vector_t* vector, void* data) {
    return vector_indexof(vector, data) != -1;
}

bool vector_contains_string(vector_t* vector, void** data, size_t length) {
    size_t i, j, k = 0;
    bool found = false;
    for (i = 0; i < vector->vector.size; i++) {
        if (!found) {
            if (vector->array[i] == data[0]) {
                found = true;
                j = i;
                k = i;
            }
        } else {
            if (vector->array[i] != data[j])
                return false;
            
            if (++j >= k + length)
                return true;
        }
    }

    return false;
}

size_t vector_getsize(vector_t* vector) {
    return vector->vector.size;
}

void** vector_toarray(vector_t* vector) {
    return vector->array;
}