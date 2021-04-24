
/** WARNING: Untested. Don't use this code yet until I go through it. */

/**
 * hashtab.c - Code definitions for a hashtable implementation.
 * 
 * Licensed per the terms found in the LICENSE file at the root of this
 * code repository.
 * 
 */

/**
 * HASHTABLE
 * A hashtable, sometimes called a dictionary or hashset (depending on
 * context and certain nuances), is a data structure that takes a key
 * and value for each data point added to it.
 * 
 * The point of doing this is to allow convenient lookup. So, you can
 * say the string "red" is associated with the number 0xFF0000, and
 * then later on, when you see the string "red" you can summon the
 * value 0xFF0000 from the hashtable.
 * 
 * This is accomplished by just storing the data in question in an
 * array, and using the string key to generate an index within the
 * array to place the item in question.
 * 
 * If two items end up possessing the same array index, that's okay!
 * The array is actually an array of pointers to the start of a linked
 * list. We just iterate through the linked list until we find the item
 * with the matching key.
 * 
 * The process of generating that unique index is called "hashing,"
 * because it generates a "hash," which is a number that you can get by
 * inputting some kind of data, but can't go in the other direction
 * and know exactly what the input data was to generate that hash.
 * 
 * TIME COMPLEXITY
 * Best: O(1) - An item possesses a totally unique index in the under-
 *              lying array structure. (Happens frequently with small
 *              data sets, making it practically as good as an array
 *              for most use cases.)
 * 
 * Typical: O(log n) - Some items in the data structure end up having
 *                     the same hash, so the data structure has to
 *                     iterate through a linked list, which is O(n).
 *                     Most items, however, aren't, which is O(1).
 *                     The resulting performance sits in the middle
 *                     of these two measures, which is O(log n).
 * 
 * Worst: O(n) - Every single item hashes to the same hash. The like-
 *               lihood of this hapening is *extremely* small, but it
 *               is nevertheless theoretically possible.
 */

#include <hashtab.h>
#include <stdlib.h>
#include <string.h>

#define BUCKET_QUANTITY 4
#define BUCKET_SIZE 0xFF
#define BUCKET_INDEX_MAXLEN 8

typedef uint8_t hash_t;

/* Non-public-facing part of the hashtable API.
   Zeros all data found in the given hashtable entry. */
void zero_entry(hashtable_entry_t* entry) {
    entry->key = NULL;
    entry->data = NULL;
    entry->next = NULL;
    entry->prev = NULL;
}

/*  Given a starting node, run the zero_entry() function
    recursively until there's nothing left to zero */
void zero_entry_recursive(hashtable_entry_t* entry) {
    if (entry->next != NULL)
        zero_entry_recursive(entry->next);
    zero_entry(entry);
}

/*  "Hash" function which, given a string key, ascertains
    the bucket index that this key would be found at. 
    Kind of a crappy hash, but it's only used to pick 1
    out of 4 arrays, so whatever. */
size_t get_bucket_index(const char* key) {
    size_t i;
    size_t ax = 0;
    size_t len = strlen(key);
    for (i = 0; i < len; i++)
        ax ^= (size_t)((key[i] * 3) >> BUCKET_QUANTITY);
    return (ax % BUCKET_QUANTITY);
}

/*  Hash function which, given a string key, determines the
    array index at which the key would be found. */
hash_t get_hash(const char* key) {
    size_t i;
    hash_t ax = 0;
    size_t len = strlen(key);
    for (i = 0; i < len; i++)
        ax ^= (hash_t)key[i];
    return ax;
}

/*  Creates a barebones hash table and zeros out its constituent data. */
hashtable_t* create_hashtable() {
    int i, j;
    hashtable_t* ret = malloc(sizeof(hashtable_t));
    ret->buckets = malloc(sizeof(hashtable_entry_t***)*BUCKET_QUANTITY);

    for (i = 0; i < BUCKET_QUANTITY; i++) {
        ret->buckets[i] = malloc(sizeof(hashtable_entry_t**)*BUCKET_SIZE);
        for (j = 0; j < BUCKET_SIZE; j++) {
            zero_entry(ret->buckets[i][j]);
        }
    }

    return ret;
}

/* Zeros out the contents of a hashtable. */
void clear_hashtable(hashtable_t* hashtable) {
    int i, j;
    for (i = 0; i < BUCKET_QUANTITY; i++)
        for (j = 0; j < BUCKET_SIZE; j++)
            zero_entry_recursive(hashtable->buckets[i][j]);
}

/* Non-public. Recursively steps through and deletes each and every
   node in the hashtable. */
void delete_step(hashtable_entry_t* entry) {
    if (entry->next != NULL)
        delete_step(entry->next);
    free(entry);
}

/* Deletes the entirety of the hashtable. */
void delete_hashtable(hashtable_t* hashtable) {
    int i,j;
    for (i = 0; i < BUCKET_QUANTITY; i++) {
        for (j = 0; j < BUCKET_SIZE; j++)
            delete_step(hashtable->buckets[i][j]);
        free(hashtable->buckets[i]);
    }

    free(hashtable->buckets);
    free(hashtable);
}

/*  Non-public. Locates the ending node of a given hashtable node, given a
    particular hash, bucket, and key, iteratively. */
hashtable_entry_t* hashtable_find_end(hashtable_t* hashtable, hash_t hash, size_t bucket, const char* key) {
    hashtable_entry_t* current;
    current = hashtable->buckets[bucket][hash];
    if (current->key == key) return NULL;
    while (current->next != NULL) {
        if (key == current->key) return NULL;
        current = current->next;
    }

    return current;
}

/* Inserts the given data into the hashtable. */
void hashtable_insert(hashtable_t* hashtable, const char* key, void* data) {
    hash_t hash = get_hash(key);
    size_t bucket = get_bucket_index(key);
    hashtable_entry_t* entry = hashtable_find_end(hashtable, hash, bucket, key);
    hashtable_entry_t* newEntry = malloc(sizeof(hashtable_entry_t));
    
    zero_entry(newEntry);
    newEntry->data = data;
    newEntry->key = key;
    entry->next = newEntry;
    newEntry->prev = entry;
}

/*  Used internally to recursively find a node by its key, given a node
    to start searching from. Returns NULL if not found. */
hashtable_entry_t* recurse_find_key(hashtable_entry_t* start, const char* key) {
    if (strcmp(start->key, key) != 0) {
        if (start->next != NULL)
            return recurse_find_key(start->next, key);
        else
            return NULL;
    } else
        return start;
}

/*  Removes the requested data from the hashtable, and frees its pointers
    --including the data within the hashtable. */
int hashtable_remove(hashtable_t* hashtable, const char* key) {
    hash_t hash = get_hash(key);
    size_t bucket = get_bucket_index(key);
    hashtable_entry_t* entry = recurse_find_key(hashtable->buckets[bucket][hash], key);
    
    if (entry == NULL)
        return 1;
    
    /* splice it out, then free its memory */
    entry->prev->data = entry->next;
    free(entry->data);
    free(entry);
    return 0;
}

/*  Retrieves the requested pointer, given a key. Returns NULL if the key
    is not found. */
void* hashtable_get(hashtable_t* hashtable, const char* key) {
    hash_t hash = get_hash(key);
    size_t bucket = get_bucket_index(key);
    return recurse_find_key(hashtable->buckets[bucket][hash], key);
}
