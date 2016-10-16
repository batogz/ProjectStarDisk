#ifndef HASHSET_H
#define HASHSET_H

struct hashset {
    int cur_size;
    int max_size;
    int8_t **data;
};

struct hashset *create_hashset(int size);

void insert(struct hashset **set, int8_t *state);

int8_t *lookup(struct hashset *set, int8_t *state);

#endif
