#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "hashset.h"

static void print_array(int *arr)
{
    for (int i = 0; i < game_size; ++i) {
        printf("%d", arr[i]);
    }
    printf("\n");
}

struct hashset *create_hashset(int size)
{
    struct hashset *set = malloc(sizeof(struct hashset));

    set->cur_size = 0;
    set->max_size = size;
    set->data = calloc(size, sizeof(int *));

    return set;
}

static unsigned long hash(int *state)
{
    //djb2
    unsigned long hash = 5381;
    for (int i = 0; i < game_size; i++) {
        hash = ((hash << 5) + hash) + state[i];
    }

    return hash;
}

static void rehash(struct hashset **set)
{
    struct hashset *set2 = create_hashset((*set)->max_size*4 + 1);
    for (int i = 0; i < (*set)->max_size; i++) {
        if ((*set)->data[i]) {
            insert(&set2, (*set)->data[i]);
        }
    }

    free((*set)->data);
    free(*set);
    *set = set2;
}

int *lookup(struct hashset *set, int *state)
{
    if (set->max_size == 0)
        printf("ERROR?!?!?\n");
    int index = hash(state) % set->max_size;

    while (set->data[index]) {
        if (memcmp(set->data[index], state, sizeof(int) * game_size) == 0)
            return set->data[index];
        index = (index + 1) % set->max_size;
    }

    return NULL;
}

void insert(struct hashset **set, int *state)
{
    // note: insert doesn't check for duplicate elements (yet)
    // will want to perform lookup first (but it's slow for now so...)
    int index = hash(state) % (*set)->max_size;

    while ((*set)->data[index])
        index = (index + 1) % (*set)->max_size;

    (*set)->data[index] = state;
    ++((*set)->cur_size);

    if ( (double) (*set)->cur_size / (*set)->max_size > 0.8f) {
        rehash(set);
    }
}
