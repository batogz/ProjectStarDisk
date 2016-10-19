#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "algo.h"
#include "game.h"
#include "hashset.h"
#include "heap.h"

static void print_array(int8_t *arr)
{
    for (int8_t i = 0; i < game_size; i++)
        printf("%d", arr[i]);
    printf("\n");
}

/*
struct p_queue_node {
    struct node *node;
    struct p_queue_node *next;
    struct p_queue_node *prev;
};

struct p_queue {
    struct p_queue_node *head;
    struct p_queue_node *tail;
};


static void print_queue(struct p_queue *queue)
{
    struct p_queue_node *node = queue->head;
    while (node) {
        printf("\t Cost %d: ", node->node->f);
        print_array(node->node->state);
        node = node->next;
    }
}


static struct p_queue *make_p_queue()
{
    struct p_queue *queue = malloc(sizeof(struct p_queue));
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

static void add_to_queue(struct p_queue *queue, struct node *node)
{
    // printf("Adding child of cost %d: ", node->f);
    // print_array(node->state);
    struct p_queue_node *qnode = malloc(sizeof(struct p_queue_node));
    qnode->node = node;

    if (!queue->head) {
        queue->head = qnode;
        queue->tail = qnode;
        qnode->next = NULL;
        qnode->prev = NULL;
        return;
    }

    struct p_queue_node *search = queue->tail;
    while (search) {
        if (search->node->f <= node->f) {
            if (search->next)
                search->next->prev = qnode;
            qnode->next = search->next;
            search->next = qnode;
            qnode->prev = search;
            if (queue->tail == search)
                queue->tail = qnode;
            return;
        }

        search = search->prev;
    }

    // adding to beginning of queue
    qnode->next = queue->head;
    queue->head->prev = qnode;
    qnode->prev = NULL;
    queue->head = qnode;
}


static struct node *queue_front(struct p_queue *queue)
{
    if (!queue->head)
        return NULL;

    struct node *node = queue->head->node;
    struct p_queue_node *old_node = queue->head;
    queue->head = queue->head->next;
    if (queue->head)
        queue->head->prev = NULL;
    free(old_node);
    return node;
}
*/

static int8_t indexof(int8_t *state, int8_t needle)
{
    for (int8_t i = 0; i < game_size; i++) {
        if (state[i] == needle)
            return i;
    }

    return -1;
}

static int8_t *swap(int8_t *state, int8_t index1, int8_t index2)
{
    int8_t *ret = malloc(game_size * sizeof(int8_t));
    if (!ret)
        exit(EXIT_FAILURE);

    memcpy(ret, state, game_size * sizeof(int8_t));

    ret[index1] = state[index2];
    ret[index2] = state[index1];

    return ret;
}

struct node *make_node(int8_t *state, struct node *parent, int8_t (*h)(int8_t *, int8_t *))
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

void expand(struct node *node, struct node **children, int8_t big_disks[],
        int8_t (*h)(int8_t *, int8_t *))
{
    int8_t index0 = node->index0;

    children[0] = make_node(
            swap(node->state, index0, index0 == 0 ? game_size - 1 : index0 - 1),
            node, h);

    children[1] = make_node(
            swap(node->state, index0, (index0 + 1) % game_size), node, h);

    int8_t jump = big_disks[index0];
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

struct node *a_star(struct hashset *set, int8_t *state, int8_t big_disks[], int8_t (*h)(int8_t *, int8_t *))
{
    Heap *fringe = create_heap();
    add(fringe, make_node(state, NULL, h));

    struct node *cur_node;
    struct node *children[4] = {};
    int8_t num_children;
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

int8_t IDA_star(struct node *n, int8_t big_disks[], int8_t (*h)(int8_t *, int8_t *), int8_t threshold, struct node ** sol)
{
    int8_t minf = 127;

    if (is_goal(n->state)){
        *sol = n;
        return 0;
    }
    if (n->f > threshold)
        return n->f;
    struct node *children[4] = {};
    int8_t num_children = (big_disks[n->index0] == 1) ? 2 : 4;
    expand(n, children, big_disks, h);
    for(int i = 0; i < num_children; i++) {
        int8_t cf = IDA_star(children[i], big_disks, h, threshold, sol);
        if (cf == 0)
            return 0;
        if (cf<minf)
            minf = cf;
    }
    return minf;
}

struct node *O_IDA_search(int8_t *state, int8_t big_disks[], int8_t (*h)(int8_t *, int8_t *))
{
    struct node *n = make_node(state, NULL, h);
    struct node *sol = n;
    int8_t threshold = n->heuristic;
    bool done = false;
    while(!done){
        int8_t newt = IDA_star(n, big_disks, h, threshold, &sol);
        if(newt==0)
            done = true;
        else threshold = newt;
    }
    return sol;
}



