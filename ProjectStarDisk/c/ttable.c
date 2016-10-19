#include <stdlib.h>
#include <string.h>

#include "ttable.h"
#include "game.h"

#define TTABLE_SIZE 65536

static int64_t **zobrist_table;

struct ttable *init_ttable()
{
    zobrist_table = calloc(game_size, sizeof(int64_t *));
    for (int i = 0; i < game_size; ++i) {
        zobrist_table[i] = calloc(disk_groups + 1, sizeof(int64_t));
        for (int j = 0; j < disk_groups + 1; ++j) {
            zobrist_table[i][j] = random();
        }
    }
    struct ttable *t = malloc(sizeof(struct ttable));
    t->data = calloc(TTABLE_SIZE, sizeof(struct ttable_node));
    return t;
}

void destroy_ttable(struct ttable *t)
{
    for (int i = 0; i < game_size; ++i) {
        free(zobrist_table[i]);
    }
    free(zobrist_table);
    for (int i = 0; i < TTABLE_SIZE; ++i) {
        if (t->data[i]) {
            free(t->data[i]->state);
            free(t->data[i]);
        }
    }
    free(t->data);
    free(t);
}

static int64_t zobrist_hash(int8_t *state)
{
    int64_t hash = zobrist_table[0][state[0]];
    for (int i = 1; i < game_size; ++i) {
        hash ^= zobrist_table[i][state[i]];
    }
    return hash;
}

static struct ttable_node *create_ttable_node(struct node *node, int threshold)
{
    struct ttable_node *tn = malloc(sizeof(struct ttable_node));
    tn->state = malloc(sizeof(int8_t) * game_size);
    memcpy(tn->state, node->state, sizeof(int8_t) * game_size);
    tn->path_cost = node->cost;
    tn->threshold = threshold;

    return tn;
}

struct ttable_node *ttable_lookup(struct ttable *t, struct node *node)
{
    int index = zobrist_hash(node->state) % TTABLE_SIZE;

    return t->data[index];
}

void ttable_insert(struct ttable *t, struct node *node, int threshold)
{
    int index = zobrist_hash(node->state) % TTABLE_SIZE;

    if (t->data[index]) {
        free(t->data[index]->state);
        free(t->data[index]);
    }

    t->data[index] = create_ttable_node(node, threshold);
}
