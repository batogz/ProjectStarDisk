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

int main(int argc, char *argv[])
{
    if (argc < 2) return 0;
    game_size = atoi(argv[1]);;
    disk_groups = sqrt(game_size - 1);
    no_states = 0;

    int8_t big_disks[game_size];
    int8_t small_disks[game_size];

    char buf[game_size];
    fgets(buf, game_size + 2, stdin);
    for (int i = 0; i < game_size; ++i) {
        big_disks[i] = buf[i] - '0';
    }

    fgets(buf, game_size + 2,  stdin);
    for (int i = 0; i < game_size; ++i) {
        small_disks[i] = buf[i] - '0';
    }

    //int8_t big_disks[] =   {1, 3, 2, 1, 3, 4, 1, 2, 2, 1, 3};
    //int8_t small_disks[] = {1, 2, 1, 0, 2, 2, 1, 3, 3, 3, 1};
    //int8_t big_disks[] =   {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 2, 4};
    //int8_t small_disks[] = {3, 2, 3, 1, 4, 3, 4, 1, 0, 1, 2, 3, 2, 4, 4, 2, 1};

    struct node *sol = a_star(small_disks, big_disks, h2);
    //struct node *sol = RBFS_wrapper(small_disks, big_disks, h2);

    if (!sol)
        printf("No solution\n");
    else
        print_sol(sol);

    return 0;
}
