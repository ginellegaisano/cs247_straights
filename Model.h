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

#define PLAYER_COUNT 4
#define MAX_HAND_COUNT 13

class Model : public Subject{
public:
	Model();											//constructor
	~Model();											//desctructor

	//accessors
	std::vector <std::pair <int, int> > getHand();
	std::vector <int> getLegalMoves();
	std::vector <std::pair <int, int> > getTable();
	std::vector <int> getWinner();
	int getDiscard(int);
	int getPlayerNum();
	bool getPlayerType();
	std::string getLastPlayedCard();
	std::string getCardName(int);
	int getScore(int);

	//mutators
	void resetPlayerScores();
	
	//methods
	void ragequit();
	bool finish();
	bool isLegalMoves(int i);
	bool gameDone();
	void makeMove(int);
	int newGame(int seed);
	void initializeDeck(bool players[4]);

private:
	std::pair <bool, std::pair <Rank ,Suit > > lastPlayedCard_;
	std::vector<int> winner;
	bool finished;
	bool playerStat[4];
	bool deal(int);
	int currentPlayer_;
	int cardsPlayed;
	int loser;
	void shuffle(long);
	Player *players[4];
	Table *table;
	Card *cards[52];
};

#endif