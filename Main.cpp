#include "Game.h"
#include <iostream>

using namespace std;


int main (int argc, char* argv[]) {
	long seed;
	if (argv[1] != NULL) seed = atoi(argv[1]);
	else seed = 0;
	srand48(seed);

	Game *game = new Game();
	game->playGame();

	delete game;
}