#include <stdio.h>
#include <stdint.h>

#include "game.h"

uint8_t game_size;

static void print_array(uint8_t *arr)
{
    for (uint8_t i = 0; i < game_size; i++)
        printf("%d", arr[i]);
    printf("\n");
}

uint8_t h1(uint8_t *big_disks, uint8_t *small_disks)
{
    uint8_t pairs = 0;
    uint8_t out_of_order_pairs = 0;

    uint8_t saw_pair = (small_disks[game_size - 1] == small_disks[0]);
    uint8_t last_pair = saw_pair ? small_disks[0] : -1;

    for (uint8_t i = 0; i < game_size; ++i) {
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

uint8_t h2(uint8_t *big_disks, uint8_t *small_disks)
{
    uint8_t pairs = 0;

    uint8_t out_of_order = 0;
    uint8_t last_num = 0;
    for (uint8_t i = 0; i < game_size; ++i) {
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

uint8_t h3(uint8_t *big_disks, uint8_t *small_disks)
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
