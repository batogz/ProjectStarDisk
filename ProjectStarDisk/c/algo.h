#ifndef ALGO_H
#define ALGO_H

#include "hashset.h"

/*
struct node {
    int8_t heuristic;
    int8_t cost;
    int8_t f;  // heuristic + cost
    struct node *parent;
    int8_t *state;
    int8_t index0;
};
*/

struct node *a_star(struct hashset *set, int8_t *state, 
        int8_t big_disks[], int8_t (*h)(int8_t *, int8_t *));

struct node *O_IDA_search(int8_t *state, int8_t big_disks[], int8_t (*h)(int8_t *, int8_t *));

#endif
