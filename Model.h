#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <map>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <string>

#include "Subject.h"
#include "Player.h"
#include "Table.h"
#include "Card.h"

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
	std::string getLastPlayedCard();
	int getScore();
	bool finish();
	bool isLegalMoves(int i);
	
	std::string getCardName(int);
	void makeMove(int);

	int newGame(int seed);
	void finishRound();
	void initializeDeck(bool players[4]);
	//void quit??
private:
	std::pair <bool, std::pair <Rank ,Suit > > lastPlayedCard_;
	bool finished;
	int cardsPlayed;
	std::vector<int> winner;
	int loser;
	bool playerStat[4];
	int currentPlayer_;
	bool deal(int);
	void shuffle(long);
	Player *players[4];
	Table *table;
	Card *cards[52];

};

#endif