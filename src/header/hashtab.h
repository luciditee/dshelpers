
/**
 * hashtab.h - Header file for all things related to the hashtable helper
 * 
 * Licensed per the terms found in the LICENSE file at the root of this
 * code repository.
 * 
 */

#ifndef __HASHTAB_H
#define __HASHTAB_H
#include <stdint.h>

typedef struct hashtable_entry hashtable_entry_t;

struct hashtable_entry {
    const char* key;
    void* data;
    hashtable_entry_t* next;
    hashtable_entry_t* prev;
};

typedef struct hashtable {
    hashtable_entry_t*** buckets;
} hashtable_t;

hashtable_t* create_hashtable();
void delete_hashtable(hashtable_t* hashtable);
void clear_hashtable(hashtable_t* hashtable);
void* hashtable_get(hashtable_t* hashtable, const char* key);
void hashtable_insert(hashtable_t* hashtable, const char* key, void* item);
int hashtable_remove(hashtable_t* hashtable, const char* key);

#endif