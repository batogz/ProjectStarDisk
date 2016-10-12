#include <stdio.h>
#include <stdlib.h>

#include "algo.h"
#include "heuristic.h"
#include "game.h"
#include "hashset.h"

int game_size;
int disk_groups;

void print_arr(int *arr)
{
    for (int i = 0; i < game_size; i++) {
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
    game_size = 10;
    disk_groups = 3;

    int big_disks[] =   {1, 3, 2, 1, 3, 4, 1, 2, 2, 1, 3};
    int small_disks[] = {1, 2, 1, 0, 2, 2, 1, 3, 3, 3, 1};

    struct node *sol = a_star(small_disks, big_disks, h1);
    if (!sol)
        printf("No solution\n");
    else
        print_sol(sol);
}
