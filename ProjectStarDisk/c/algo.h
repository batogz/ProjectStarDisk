#ifndef ALGO_H
#define ALGO_H

struct node {
    int heuristic;
    int cost;
    int f;  // heuristic + cost
    struct node *parent;
    int *state;
    int index0;
};

struct node *a_star(int *state, int big_disks[], int (*h)(int *, int *));
#endif
