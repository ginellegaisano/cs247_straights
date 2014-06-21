#ifndef _PLAYER_
#define _PLAYER_

#include "Card.h"
#include "Command.h"
#include "Status.h"
#include <vector>

//entity ADT
class Player {
	public:
		Player(bool); //
		virtual ~Player();
		void setHand(std::vector<Card*>);
		Command makeMove(Table&);
		int getScore();
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
// bool checkLegalMoves(Card*); //checks if playing a card is legal
		// std::vector<Card*> getHand();
		// std::vector<Card*> getDiscard();
// virtual bool play(Card&) = 0;
		// virtual bool discard(Card&) = 0;
		// int getScore();
		// virtual void makeMove(Command) = 0;