
/**
 * bintree.h - Header file for all things binary-tree-related
 * 
 * Licensed per the terms found in the LICENSE file at the root of this
 * code repository.
 * 
 */

#ifndef __BINTREE_H
#define __BINTREE_H
#include <stddef.h>

/* C89 does not guarantee stdbool.h */
#define bool int
#define true 1
#define false 0

typedef struct bintree_node bintree_node_t;

struct bintree_node {
    bintree_node_t* left;
    bintree_node_t* right;
    void* data;
};

size_t bintree_count_nodes(bintree_node_t* start);
int  bintree_get_height(bintree_node_t* start);
void bintree_invert(bintree_node_t* start);
bool bintree_is_hbalanced(bintree_node_t* start);

#endif