#ifndef _HUMAN_
#define _HUMAN_

#include "Status.h"
#include "Card.h"
#include "Table.h"
#include <vector>


//entity ADT
class Human : public Status {
public:
	Human();
	virtual ~Human();
	void makeMove(Card* card,Table&, std::vector<Card*>&, std::vector<Card*>&); //print hand, play, discard, quit
private:
	Human(Human&);
	Human& operator= (Human&);
};
//exceptions: Illegal play and Illegal discard

#endif