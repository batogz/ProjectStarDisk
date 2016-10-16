#ifndef GAME_H
#define GAME_H

// size of the game circle (global!)
extern int8_t game_size;

// number of groups of small disks
extern int8_t disk_groups;

// number of states inserted;
extern int no_states;

// returns 1 if the game is won and 0 otherwise
int8_t is_goal(int8_t *small_disks);

#endif
