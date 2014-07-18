#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <map>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <cassert>

#include "Subject.h"
#include "Player.h"
#include "Table.h"
#include "Card.h"

Card *cards_[52];

class Model : public Subject{
public:
	Model();
	~Model();
	std::vector <std::pair <int, int> > getHand();
	std::vector <int> getLegalMoves();
	std::vector <std::pair <int, int> > getTable();
	std::vector <int> getWinner();

	void ragequit();


	int getPlayerNum();
	bool getPlayerType();
	int getScore();
	bool finish();
	

	void makeMove(int);

	int newGame(int seed);
	void finishRound();
	void initializeDeck(bool players[4]);
	//void quit??
private:
	bool finished;
	int cardsPlayed;
	std::vector<int> winner;
	int loser;
	bool playerStat[4];
	int currentPlayer_ = 2;
	bool deal(int);
	void shuffle(int);
	Player *players[4];
	Table *table;
};

#endif