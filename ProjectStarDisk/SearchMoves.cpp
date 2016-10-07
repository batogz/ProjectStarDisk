#include "SearchMoves.h"

using namespace std;

int bestPathOfDepth(int path[], int state[], int bases[], int depth) {
	int *xlState, *xrState, *olState, *orState;
	int* xlPath[SRCHDPTH], xrPath[SRCHDPTH], olPath[SRCHDPTH], orPath[SRCHDPTH];
	int pairs = 0, i, openTop;
	int maxPairs = 0, tempPairs, nextStep;

	xlState = (int*)malloc(BOTS*sizeof(int));
	xrState = (int*)malloc(BOTS*sizeof(int));
	olState = (int*)malloc(BOTS*sizeof(int));
	orState = (int*)malloc(BOTS*sizeof(int));

	for (i = 0; i < BOTS; i++) {
		if (i == BOTS) {
			if (state[i] == state[0])pairs++;
		}
		else {
			if (state[i] == state[i + 1])pairs++;
		}
	}

	if (depth >= SRCHDPTH) return pairs;
	if (pairs >(N - 1)*N - 1) {
		return 0;
	}

	openTop = 0;
	while (openTop < BOTS) {
		if (state[openTop] == 0) {
			break;
		}
		else {
			openTop++;
		}
	}
	for (i = 0; i < BOTS; i++) {
		olState[i] = state[i];
		orState[i] = state[i];
		xlState[i] = state[i];
		xrState[i] = state[i];
		if (path[i] > 0) {
			xlPath[i] = path[i];
			xrPath[i] = path[i];
			olPath[i] = path[i];
			orPath[i] = path[i];
		}
	}
	if (bases[openTop]>1) {
		xlPath[depth] = 3;
		simMove(xlState, openTop, -bases[openTop]);
		tempPairs = bestPathOfDepth(xlPath, xlState, bases, depth + 1);
		if (tempPairs > maxPairs) {
			maxPairs = tempPairs;
			nextStep = xlPath[depth];
		}
		else {
			free(xlPath);
			free(xlState);
		}

		xrPath[depth] = 4;
		simMove(xrState, openTop, bases[openTop]);
		tempPairs = bestPathOfDepth(xrPath, xrState, bases, depth + 1);
		if (tempPairs > maxPairs) {
			maxPairs = tempPairs;
			nextStep = xrPath[depth];
		}
		else {
			free(xrPath);
			free(xrState);
		}
	}
	olPath[depth] = 1;
	simMove(olState, openTop, -1);
	tempPairs = bestPathOfDepth(olPath, olState, bases, depth - 1);
	if (tempPairs > maxPairs) {
		maxPairs = tempPairs;
		nextStep = olPath[depth];
	}
	else {
		free(olPath);
		free(olState);
	}

	orPath[depth] = 2;
	simMove(orState, openTop, 1);
	tempPairs = bestPathOfDepth(orPath, orState, bases, depth - 1);
	if (tempPairs > maxPairs) {
		maxPairs = tempPairs;
		nextStep = orPath[depth];
	}
	else {
		free(orPath);
		free(orState);
	}

	path[depth] = nextStep;
	return maxPairs;
}

int simMove(int state[], int openTop, int dist) {
	int pairs = 0;
	if (openTop + dist < 0) {
		state[openTop] = state[openTop + dist + BOTS];
		state[openTop + dist + BOTS] = 0;
	}
	else if (openTop + dist > BOTS - 1) {
		state[openTop] = state[openTop + dist - BOTS];
		state[openTop + dist - BOTS] = 0;
	}
	else {
		state[openTop] = state[openTop + dist];
		state[openTop + dist] = 0;
	}

	return pairs;
}

void makeMove(int depth, int bases[], int state[], ofstream &outFile) {
	int pairs = 0, i, openTop, path[SRCHDPTH], nState[BOTS];
	string stateOut = "";

	for (i = 0; i < depth; i++) {
		stateOut.append("\t");
	}
	stateOut.append("|");

	for (i = 0; i < BOTS; i++) {
		if (i == BOTS) {
			if (state[i] == state[0])pairs++;
		}
		else {
			if (state[i] == state[i + 1])pairs++;
		}
		stateOut.append(to_string(state[i]) + "|");
	}

	outFile << stateOut;
	outFile << "  ";
	outFile << depth;
	outFile << "/";
	outFile << (N - 1)*N - pairs;
	outFile << "/";
	outFile << depth + (N - 1)*N - pairs;
	outFile << "\n";
	if (pairs >(N - 1)*N - 1) {
		return;
	}

	openTop = 0;
	while (openTop < BOTS) {
		if (state[openTop] == 0) {
			break;
		}
		else {
			openTop++;
		}
	}

	for (i = 0; i < SRCHDPTH; i++) {
		path[i] = 0;
	}

	bestPathOfDepth(path, state, bases, 0);

	for (i = 0; i < BOTS; i++) {
		nState[i] = state[i];
	}
	switch (path[0]) {
	case 3:
		simMove(nState, openTop, -bases[openTop]);
		makeMove(depth + 1, bases, nState, outFile);
		break;
	case 4:
		simMove(nState, openTop, bases[openTop]);
		makeMove(depth + 1, bases, nState, outFile);
		break;
	case 1:
		simMove(nState, openTop, -1);
		makeMove(depth + 1, bases, nState, outFile);
		break;
	case 2:
		simMove(nState, openTop, 1);
		makeMove(depth + 1, bases, nState, outFile);
		break;
	default:
		break;
	}
}