#ifndef _COMPUTER_
#define _COMPUTER_

#include "Status.h"
#include "Card.h"
#include "Table.h"
#include <vector>
#include "Command.h"

//entity ADT
class Computer : public Status {
	public:
		Computer();
		virtual ~Computer();
		Command makeMove(Table&, std::vector<Card*>&, std::vector<Card*>&, int playerNum); //play, discard
	private:
		Computer(Computer&);
		Computer& operator= (Computer&);
};

#endif