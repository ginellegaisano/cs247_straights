#ifndef _TABLE_
#define _TABLE_

#include <set>
#include "Card.h"
#include <vector>


class Table {
	public:
		Table();
		~Table();
		void printStacks();
		std::set<std::string> getLegalCards(); //so that can be used to print
		void addToStacks(Card);
		bool isLegalCard(Card);
		void clearTable();
	private:
		void updateLegalCards(Card); //called when we add to a stack
		std::vector<int> stacks_[4];
		std::set<std::string> legalCards_; 

};

#endif