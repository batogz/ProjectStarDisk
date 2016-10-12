#include "game.h"

// returns 1 if the game is won and 0 otherwise
int is_goal(int *small_disks)
{
    for (int i = 0; i < game_size; ++i) {
        int next = (i+1) % game_size;
        if (small_disks[i] != small_disks[next] && 
                small_disks[i] + 1 != small_disks[next] &&
                small_disks[next] != 0)
            return 0;
    }

    return 1;
}
