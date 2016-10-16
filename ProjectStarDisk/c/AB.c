#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "algo.h"
#include "heuristic.h"
#include "game.h"
#include "hashset.h"

int8_t game_size;
int8_t disk_groups;
int no_states;

void print_arr(int8_t *arr)
{
    for (int8_t i = 0; i < game_size; i++) {
        printf("%d", arr[i]);
    }
    printf("\n");
}

void print_sol(struct node *sol)
{
    if (!sol)
        return;

    print_sol(sol->parent);
    //printf("%d cost: ", sol->f);
    print_arr(sol->state);
}

int main()
{
    game_size = 17;
    disk_groups = 4;
    no_states = 0;

    //int8_t big_disks[] =   {1, 3, 2, 1, 3, 4, 1, 2, 2, 1, 3};
    //int8_t small_disks[] = {1, 2, 1, 0, 2, 2, 1, 3, 3, 3, 1};
    int8_t big_disks[] =   {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 2, 4};
    int8_t small_disks[] = {0, 2, 1, 4, 2, 3, 2, 1, 3, 3, 3, 1, 1, 4, 2, 4, 4};

    struct node *sol = a_star(small_disks, big_disks, h2);
    //struct node *sol = RBFS_wrapper(small_disks, big_disks, h2);

    if (!sol)
        printf("No solution\n");
    else
        print_sol(sol);
}
