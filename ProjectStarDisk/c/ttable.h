#ifndef TTABLE_H
#define TTABLE_H

#include "heap.h"
 
/* Transposition table */

struct ttable_node {
    int8_t *state;
    int path_cost;
    int threshold;
};

struct ttable {
    struct ttable_node **data;
};

struct ttable *init_ttable();

/* insert doubles as replace! */
void ttable_insert(struct ttable *, struct node *, int threshold);

struct ttable_node *ttable_lookup(struct ttable *, struct node *);

#endif
