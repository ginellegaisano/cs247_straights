#ifndef CONTROLLER_H
#define CONTROLLER_H

//#include <gtkmm.h>
#include <stdio.h>
#include "Model.h"
#include <vector>
#include <string>

class Controller {
public:
	Controller( Model*  m);
	//called once when window is opened
	void initializeDeck(std::vector<bool> players);

	//functions associated with each button click.
	void startNewGame(int seedNum);
	void rageQuit();
	void quitGame();
	void resetPlayerScores();
	bool playCard(int);
	void finishRound(); //dont know if i should remove this...

	//get statements. information?
	int getPlayerNum();
	int getDiscard(int);
	// std::string getCardName(int);
	std::string getLastPlayedCard();
	std::vector<int> getLegalMoves();
	std::vector<std::pair<int, int> > getTable();
	std::vector<std::pair<int, int> > getHand();
	std::vector<int> getWinner();
	bool getPlayerType();
	int getScore(int);
	bool finished();
	bool gameDone();


private:
	Model *model_;
};

#endif