#include "Game.h"
#include <iostream>

using namespace std;


int main (int argc, char* argv[]) {
	long num;
	if (argv[1] != NULL) num = atoi(argv[1]);
	else num = 0;
	srand48(num);

	Game *game = new Game();
	game->playGame();

	delete game;
}