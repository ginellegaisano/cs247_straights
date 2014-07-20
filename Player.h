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
	int getDiscardPileSize();
	void setHand(std::vector<Card*>);
	void makeMove(Card*, Table&);
	int getScore();
	void calculateScore();
	std::vector<Card*>* getHand();
	void printDiscards();
	void clearCards();
	void rageQuit();
	void newGame(); 
private:
	Player& operator= (Player&);
	Player(Player&);
	std::vector<Card*>* hand_;
	std::vector<Card*>* discardPile_;
	int score_;
	Status* status_;

};

#endif
