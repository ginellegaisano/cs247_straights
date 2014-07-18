#ifndef _PLAYER_
#define _PLAYER_

#include "Card.h"
#include "Status.h"
#include <vector>

//entity ADT
class Player {
public:
	Player(bool); //
	virtual ~Player();
	void setHand(std::vector<Card*>);
	void makeMove(Card*, Table&);
	int getScore();
	std::vector<Card*>* getHand;
	void calculateScore();
	void printDiscards();
	void clearCards();
	void rageQuit();
private:
	Player& operator= (Player&);
	Player(Player&);
	std::vector<Card*>* hand_;
	std::vector<Card*>* discardPile_;
	int score_;
	Status* status_;

};

#endif
