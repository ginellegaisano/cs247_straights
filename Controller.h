#ifndef CONTROLLER_H
#define CONTROLLER_H

//#include <gtkmm.h>
#include <stdio.h>
#include "Model.h"
#include <vector>

class Controller {
public:
	Controller( Model*  m);
	//called once when window is opened
	void initializeDeck(std::vector<bool> players);

	//functions associated with each button click.
	void startNewGame(int seedNum);
	void rageQuit();
	void quitGame();
	bool playCard(int);
	void finishRound(); //dont know if i should remove this...

	//get statements. information?
	int getPlayerNum();
	std::vector<int> getLegalMoves();
	std::vector<std::pair<int, int> > getTable();
	std::vector<std::pair<int, int> > getHand();
	bool getPlayerType();
	int getScore();
	bool finished();

private:
	Model *model_;
};

#endif