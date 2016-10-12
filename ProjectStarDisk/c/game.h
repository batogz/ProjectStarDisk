#ifndef GAME_H
#define GAME_H

// size of the game circle (global!)
extern int game_size;

// number of groups of small disks
extern int disk_groups;

// returns 1 if the game is won and 0 otherwise
int is_goal(int *small_disks);

#endif
