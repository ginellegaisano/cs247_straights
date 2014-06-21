#define CARD_COUNT 52

#include "Player.h"
#include "Table.h"
#include <stdlib.h>
#include <cstdlib>
#include "Card.h"
#include "Command.h"
#include <cassert>
#include <iostream>
#include "Global.h"

class Game {
	public: 
		Game();
		~Game();
		void playGame();
	private:
		void shuffle();
		void initializeDeck();
		bool deal(int);
		void endRound();
		void quit(Player *players[4], Table* table);
		Player *players[4];
		Table *table;

};
