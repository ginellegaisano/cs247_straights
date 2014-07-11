#ifndef VIEW_H
#define VIEW_H

#include <Game.h>
#include <Player.h>

class Subject {
	public:
		subscribe (Player*);
		unsubscribe(Player*);
	private:
		Player *player; //subscribe to a player
		Game *game;
	protected:
		notify();
};

#endif