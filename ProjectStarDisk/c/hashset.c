#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "game.h"
#include "hashset.h"

static void print_array(int8_t *arr)
{
    for (int8_t i = 0; i < game_size; ++i) {
        printf("%d", arr[i]);
    }
    printf("\n");
}

struct hashset *create_hashset(int size)
{
    struct hashset *set = malloc(sizeof(struct hashset));

    set->cur_size = 0;
    set->max_size = size;
    set->data = calloc(size, sizeof(struct node *));

    return set;
}

static unsigned long hash(int8_t *state)
{
    //djb2
    unsigned long hash = 5381;
    for (int i = 0; i < game_size; i++) {
        hash = ((hash << 5) + hash) + state[i];
    }

    return hash;
}

static void rehash(struct hashset *set)
{
    int old_max = set->max_size;
    struct node **old_data = set->data;
    struct node **data2 = calloc(old_max * 4 + 1, sizeof(struct node *));
    set->data = data2;
    set->cur_size = 0;
    set->max_size = old_max * 4 + 1;
    for (int i = 0; i < old_max; i++) {
        if (old_data[i]) {
            insert(set, old_data[i]);
        }
    }

    free(old_data);
}

struct node *lookup(struct hashset *set, struct node *node)
{
    int index = hash(node->state) % set->max_size;

    while (set->data[index]) {
        if (memcmp(set->data[index]->state, node->state, sizeof(int8_t) * game_size) == 0)
            return set->data[index];
        index = (index + 1) % set->max_size;
    }

    return NULL;
}

int no_states;

void insert(struct hashset *set, struct node *node)
{
    int index = hash(node->state) % set->max_size;

    while (set->data[index]) {
        index = (index + 1) % set->max_size;
    }
    set->data[index] = node;
    ++(set->cur_size);
    no_states++;

    if ( (double) set->cur_size / set->max_size > 0.8f) {
        rehash(set);
    }
}
