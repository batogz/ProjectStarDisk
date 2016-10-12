#include <stdio.h>

#include "game.h"

int h1(int *big_disks, int *small_disks)
{
    int pairs = 0;
    int out_of_order_pairs = 0;

    int saw_pair = (small_disks[game_size - 1] == small_disks[0]);
    int last_pair = saw_pair ? small_disks[0] : -1;

    for (int i = 0; i < game_size; ++i) {
        if (small_disks[i] == small_disks[(i+1) % game_size]) {
            pairs++;

            if (saw_pair && last_pair != small_disks[i]) {
                out_of_order_pairs++;
            }

            last_pair = small_disks[i];
            saw_pair = 1;
        } else {
            saw_pair = 0;
        }
    }

    return disk_groups * (disk_groups - 1) - pairs + out_of_order_pairs;
}

int h2(int *big_disks, int *small_disks)
{
    return 0;
}
