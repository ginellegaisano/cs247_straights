#ifndef _STATUS_
#define _STATUS_

#include "Table.h"
#include "Card.h"
#include <vector>
#include "Command.h"

class Status {
	public:
		Status();
		virtual ~Status();
		virtual Command makeMove(Table&, std::vector<Card*>&, std::vector<Card*>&) = 0;
	protected:
		void play(Table&, Card&, std::vector<Card*>&);
		void discard(Table&, Card&, std::vector<Card*>&, std::vector<Card*>&);
		int isInHand(Card, std::vector<Card*>&);

};

#endif