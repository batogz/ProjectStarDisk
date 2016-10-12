#ifndef HASHSET_H
#define HASHSET_H

struct hashset {
    int cur_size;
    int max_size;
    int **data;
};

struct hashset *create_hashset(int size);

void insert(struct hashset **set, int *state);

int *lookup(struct hashset *set, int *state);

#endif
