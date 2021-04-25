/** WARNING: Untested. Don't use this code yet until I go through it. */

/**
 * bintree.c - Code definitions for a binary tree data structure.
 * 
 * Licensed per the terms found in the LICENSE file at the root of this
 * code repository.
 * 
 */

#include <bintree.h>

#define MAX(i,j) (i > j ? i : j)

/* Internally used recursive-strategy count of binary tree nodes. */
size_t count_internal(bintree_node_t* s, size_t c) {
    if (s == NULL) return c;
    else {
        if (s->left != NULL)
            c = count_internal(s->left, ++c);
        if (s->right != NULL)
            c = count_internal(s->right, ++c);
    }

    return c;
}

/* Returns the number of non-null nodes in a binary tree. */
size_t bintree_count_nodes(bintree_node_t* start) {
    size_t ret = 0;
    return count_internal(start, ret);
}

/* "Invert" (reverse/flip) a binary tree */
void bintree_invert(bintree_node_t* start) {
    if (start == NULL) return;
    
    bintree_node_t* temp = start->left;
    start->left = start->right;
    start->right = start->left;
    
    if (start->left != NULL)
        bintree_invert(start->left);
    if (start->right != NULL)
        bintree_invert(start->right);
}

/* Fast absolute value function, idea stolen from 
   this fantastic SO question. Avoids branching:
   https://stackoverflow.com/a/2074403/3941696 */
int abs(int i) {
    int j = i;
    int temp = i >> (sizeof(int)-1);
    j ^= temp;
    j += temp & 1;
    return j;
}

int bintree_get_height(bintree_node_t* n) {
    if (n == NULL)
        return 0;
    int l = bintree_get_height(n->left);
    int r = bintree_get_height(n->right);
    return MAX(l,r) + 1;
}

bool bintree_is_hbalanced(bintree_node_t* n) {
    if (n == NULL) return true;
    return abs(bintree_get_height(n->left) 
        - bintree_get_height(n->right)) <= 1
        && bintree_is_hbalanced(n->left)
        && bintree_is_hbalanced(n->right);
}

