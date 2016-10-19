#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "algo.h"
#include "heuristic.h"
#include "game.h"
#include "hashset.h"
#include "heap.h"

int8_t game_size;
int8_t disk_groups;
int no_states;

void print_arr(int8_t *arr)
{
    for (int8_t i = 0; i < game_size - 1; i++) {
        printf("%d ", arr[i]);
    }
    printf("%d\n",arr[game_size-1]);
}

void print_sol(struct node *sol)
{
    if (!sol)
        return;

    print_sol(sol->parent);
    //printf("%d cost: ", sol->f);
    fprintf(stderr, "H: %2d : Path %2d : Eval %2d : ", sol->heuristic, sol->cost, sol->f);
    print_arr(sol->state);
}

int main(int argc, char *argv[])
{
    if (argc < 2) return 0;
    game_size = atoi(argv[1]);;
    disk_groups = sqrt(game_size - 1);
    no_states = 0;

    int8_t big_disks[game_size];
    int8_t small_disks[game_size];

    char buf[game_size * 2 - 1];
    fgets(buf, game_size * 2 + 10, stdin);
    for (int i = 0; i < game_size * 2 - 1; i = i+2) {
        big_disks[i/2] = buf[i] - '0';
    }

    fgets(buf, game_size * 2+ 10,  stdin);
    for (int i = 0; i < game_size * 2 - 1; i = i+2) {
        small_disks[i/2] = buf[i] - '0';
    }

    //print_arr(big_disks);
    //print_arr(small_disks);

    //int8_t big_disks[] =   {1, 3, 2, 1, 3, 4, 1, 2, 2, 1, 3};
    //int8_t small_disks[] = {1, 2, 1, 0, 2, 2, 1, 3, 3, 3, 1};
    //int8_t big_disks[] =   {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 2, 4};
    //int8_t small_disks[] = {3, 2, 3, 1, 4, 3, 4, 1, 0, 1, 2, 3, 2, 4, 4, 2, 1};

    //struct node *sol = RBFS_wrapper(small_disks, big_disks, h2);
    //int8_t big_disks[] =   {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1};
    //int8_t small_disks[] = {2, 4, 3, 1, 4, 2, 3, 4, 0, 1, 3, 2, 4, 2, 1, 1, 3};

    struct hashset *set = NULL;
    struct node *sol = NULL;
    if (disk_groups >= 100) {
        set = create_hashset(311);
        sol = a_star(set, small_disks, big_disks, h2);
    }
    else {
        sol = O_IDA_search(small_disks, big_disks, h2);
    }

    if (!sol)
        printf("No solution\n");
    else {
        printf("Solution is\n");
        print_sol(sol);
    }

    if (set) {
        for (int i = 0; i < set->max_size; ++i) {
            if (set->data[i]) {
                if (set->data[i]->state != small_disks)
                    free(set->data[i]->state);
                free(set->data[i]);
            }
        }
        free(set->data);
        free(set);
        sol = NULL;
    }

    struct node *n = sol;
    while (n) {
        struct node *n1 = n->parent;
        if (n->state != small_disks) free(n->state);
        free(n);
        n = n1;
    }

    return 0;
}
