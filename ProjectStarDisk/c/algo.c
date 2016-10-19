#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "algo.h"
#include "game.h"
#include "hashset.h"
#include "heap.h"
#include "ttable.h"

static void print_array(uint8_t *arr)
{
    for (uint8_t i = 0; i < game_size; i++)
        printf("%d", arr[i]);
    printf("\n");
}

static uint8_t indexof(uint8_t *state, uint8_t needle)
{
    for (uint8_t i = 0; i < game_size; i++) {
        if (state[i] == needle)
            return i;
    }

    return -1;
}

static uint8_t *swap(uint8_t *state, uint8_t index1, uint8_t index2)
{
    uint8_t *ret = malloc(game_size * sizeof(uint8_t));
    if (!ret)
        exit(EXIT_FAILURE);

    memcpy(ret, state, game_size * sizeof(uint8_t));

    ret[index1] = state[index2];
    ret[index2] = state[index1];

    return ret;
}

struct node *make_node(uint8_t *state, struct node *parent, uint8_t (*h)(uint8_t *, uint8_t *))
{
    struct node *node = malloc(sizeof(struct node));
    if (!node)
        exit(EXIT_FAILURE);

    node->heuristic = h(NULL, state);
    node->parent = parent;
    node->state = state;
    node->index0 = indexof(state, 0);

    if (!parent)
        node->cost = 0;
    else
        node->cost = parent->cost + 1;

    node->f = node->cost + node->heuristic;

    //if(no_states % 1000 == 0){
    //    printf("%d ", no_states);
    //    printf("%d\n", node->cost);
    //    print_array(state);
    //}

    return node;
}

void expand(struct node *node, struct node **children, uint8_t big_disks[],
        uint8_t (*h)(uint8_t *, uint8_t *))
{
    uint8_t index0 = node->index0;

    children[0] = make_node(
            swap(node->state, index0, index0 == 0 ? game_size - 1 : index0 - 1),
            node, h);

    children[1] = make_node(
            swap(node->state, index0, (index0 + 1) % game_size), node, h);

    uint8_t jump = big_disks[index0];
    if (jump == 1)
        return;

    children[2] = make_node(
            swap(node->state, index0, index0 < jump ?
                game_size - jump + index0 : index0 - jump),
            node, h);

    children[3] = make_node(
            swap(node->state, index0, (index0 + jump) % game_size), node, h);

}

int no_states;

struct node *a_star(struct hashset *set, uint8_t *state, uint8_t big_disks[], uint8_t (*h)(uint8_t *, uint8_t *))
{
    Heap *fringe = create_heap();
    add(fringe, make_node(state, NULL, h));

    struct node *cur_node;
    struct node *children[4] = {};
    uint8_t num_children;
    //int i = 0;
    while ((cur_node = pop(fringe))) {
        //if (i++ % 1000 == 0) fprintf(stderr, "%d\n", i);

        if (is_goal(cur_node->state)) {
            delete_heap(fringe);
            return cur_node;
        }

        if (!lookup(set, cur_node)) {
            insert(set, cur_node);

            num_children = (big_disks[cur_node->index0] == 1) ? 2 : 4;

            expand(cur_node, children, big_disks, h);

            for (int i = 0; i < num_children; i++) {
                add(fringe, children[i]);
            }

        } else {
            free(cur_node->state);
            free(cur_node);
        }
    }

    return NULL;
}

static uint8_t IDA_star(struct node *n, uint8_t big_disks[], uint8_t (*h)(uint8_t *, uint8_t *), 
        uint8_t threshold, struct node ** sol, struct ttable *t, int deeper)
{
    uint8_t minf = 127;

    ttable_insert(t, n, threshold);

    if (is_goal(n->state)){
        *sol = n;
        return 0;
    }
    if (n->f > threshold) {
        return n->f;
    }
    struct node *children[4] = {};
    uint8_t num_children = (big_disks[n->index0] == 1) ? 2 : 4;
    expand(n, children, big_disks, h);
    for(int i = 0; i < num_children; i++) {
        struct ttable_node *ln = ttable_lookup(t, children[i]);

        if (ln
            && (memcmp(ln->state, children[i]->state, sizeof(uint8_t) * game_size) == 0)
            && ln->threshold == threshold
            //&& ln->path_cost <= n->cost
           ) {
            if ((deeper && ln->path_cost <= n->cost) || 
                    (!deeper && ln->threshold == threshold)) {
                free(children[i]->state);
                free(children[i]);
                continue;

            }
        }

        uint8_t cf = IDA_star(children[i], big_disks, h, threshold, sol, t, deeper);
        if (cf == 0) {
            //goal
            for (int j = i + 1; j < num_children; j++) {
                free(children[j]->state);
                free(children[j]);
            }
            return 0;
        }
        if (cf<minf)
            minf = cf;
        free(children[i]->state);
        free(children[i]);
    }
    return minf;
}

struct node *O_IDA_search(uint8_t *state, uint8_t big_disks[],
        uint8_t (*h)(uint8_t *, uint8_t *), int deeper)
{
    struct ttable *t = init_ttable();
    struct node *n = make_node(state, NULL, h);
    struct node *sol = n;
    uint8_t threshold = n->heuristic;
    bool done = false;
    while(!done){
        //fprintf(stderr, "Threshold %d\n", threshold);
        uint8_t newt = IDA_star(n, big_disks, h, threshold, &sol, t, deeper);
        if(newt==0)
            done = true;
        else threshold = newt;
        if (threshold == 127) return NULL;
    }
    destroy_ttable(t);
    return sol;
}



