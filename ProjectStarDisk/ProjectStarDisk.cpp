#include "ProjectStarDisk.h"
#include "SearchMoves.h"

using namespace std;

int main() {
	int bases[BOTS], tops[BOTS], seed;
	int i, baseCount[N + 1], topCount[N];
	ofstream outFile;

	for (i = 0; i < N; i++) {
		topCount[i] = N;
	}
	baseCount[N] = 1;
	for (i = 0; i < BOTS; i++) {
		bases[i] = rand() % (N + 1) + 1;

		if (i == 0) {
			tops[i] = 0;
		}
		else {
			seed = rand() % N + 1;
			while (topCount[seed - 1] < 1) {
				seed = rand() % N + 1;
			}
			topCount[seed - 1]--;
			tops[i] = seed;
		}
	}

	cout << "finished generating \n";

	outFile.open("testTree.txt");


	outFile << "|";
	for (i = 0; i < BOTS; i++) {
		outFile << bases[i];
		outFile << "|";
	}
	outFile << "\n";

	makeMove(0, bases, tops, outFile);
}