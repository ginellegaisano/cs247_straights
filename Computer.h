#ifndef _COMPUTER_
#define _COMPUTER_

#include "Status.h"
#include "Card.h"
#include "Table.h"
#include <vector>

//entity ADT
class Computer : public Status {
public:
	Computer();
	virtual ~Computer();
	void makeMove(Card*, Table&, std::vector<Card*>&, std::vector<Card*>&); //play, discard
private:
	Computer(Computer&);
	Computer& operator= (Computer&);
};

#endif