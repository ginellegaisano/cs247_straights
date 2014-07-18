#ifndef CONTROLLER_H
#define CONTROLLER_H

//#include <gtkmm.h>
#include <stdio.h>

class Model;

class Controller{
public:
	Controller(Model*);
	bool playCard(int, int);
	void newGame(int seedNum);
	void rageQuit(int playerNum);
private:
	Model *model_;
};

#endif
