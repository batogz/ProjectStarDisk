#include <stdio.h>
#include <stdint.h>

#include "game.h"

int8_t game_size;

static void print_array(int8_t *arr)
{
    for (int8_t i = 0; i < game_size; i++)
        printf("%d", arr[i]);
    printf("\n");
}

int8_t h1(int8_t *big_disks, int8_t *small_disks)
{
    int8_t pairs = 0;
    int8_t out_of_order_pairs = 0;

    int8_t saw_pair = (small_disks[game_size - 1] == small_disks[0]);
    int8_t last_pair = saw_pair ? small_disks[0] : -1;

    for (int8_t i = 0; i < game_size; ++i) {
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
    //if(disk_groups * (disk_groups - 1) - pairs + 2*out_of_order_pairs < 3)print_array(small_disks);
    return disk_groups * (disk_groups - 1) - pairs + 2*out_of_order_pairs;
}

int8_t h2(int8_t *big_disks, int8_t *small_disks)
{
    int8_t pairs = 0;

    int8_t out_of_order = 0;
    int8_t last_num = 0;
    for (int8_t i = 0; i < game_size; ++i) {
        if (small_disks[i] == small_disks[(i+1) % game_size]) {
            pairs++;
        }

        if (small_disks[i] != last_num && small_disks[i] != last_num + 1) {
            out_of_order++;
        }
        last_num = small_disks[i];
    }
    //if(2*(disk_groups * (disk_groups - 1) - pairs) + out_of_order < 4)print_array(small_disks);
    return (disk_groups * (disk_groups - 1) - pairs) + out_of_order;
}

int8_t h3(int8_t *big_disks, int8_t *small_disks)
{
    int count = 0;
    for (int i = 0; i < game_size; ++i) {
        int next = (i+1) % game_size;
        if (small_disks[i] != small_disks[next] && 
                small_disks[i] + 1 != small_disks[next] &&
                small_disks[next] != 0)
            count++;
    }

    return count;
}
