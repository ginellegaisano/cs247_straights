#ifndef VIEW_H
#define VIEW_H

#include <Game.h>
#include <Player.h>

class Subject {
	public:
		subscribe (Observer*);
		unsubscribe(Observer*);
	private:
		Player *player; //subscribe to a player
		Game *game;
	protected:
		notify();
};

#endif