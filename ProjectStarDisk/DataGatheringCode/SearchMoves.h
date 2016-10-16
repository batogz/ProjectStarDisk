#include "ProjectStarDisk.h"

#define SRCHDPTH	2

int bestPathOfDepth(int path[], int state[], int bases[], int depth);

int simMove(int state[], int openTop, int dist);

void makeMove(int depth, int bases[], int state[], std::ofstream &outFile);