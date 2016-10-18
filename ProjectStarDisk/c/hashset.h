#ifndef HASHSET_H
#define HASHSET_H

#include "heap.h"

struct hashset {
    int cur_size;
    int max_size;
    struct node **data;
};

struct hashset *create_hashset(int size);

void insert(struct hashset *set, struct node *state);

struct node *lookup(struct hashset *set, struct node *state);

#endif
