#ifndef ALGO_H
#define ALGO_H

#include "hashset.h"

/*
struct node {
    uint8_t heuristic;
    uint8_t cost;
    uint8_t f;  // heuristic + cost
    struct node *parent;
    uint8_t *state;
    uint8_t index0;
};
*/

struct node *a_star(struct hashset *set, uint8_t *state, 
        uint8_t big_disks[], uint8_t (*h)(uint8_t *, uint8_t *));

struct node *O_IDA_search(uint8_t *state, uint8_t big_disks[], uint8_t (*h)(uint8_t *, uint8_t *), int deeper);

#endif
