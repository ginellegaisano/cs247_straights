#include "Table.h"
#include <set>
#include "Card.h"
#include <vector>
#include <iostream>

//need to initialize legal cards with 7S
Table::Table(){
	legalCards_.insert("7S");
}
Table::~Table(){}

//returns true if card is in legal cards
bool Table::isLegalCard(Card card) {
	if (legalCards_.find(card.getCardName(card.getRank(), card.getSuit())) != legalCards_.end()) {
		return true;
	}
	else {
		return false;
	}
}

//prints cards on the table
void Table::printStacks() {
	std::cout << "Cards on the table: \n";
	for (int i = 0; i < SUIT_COUNT; i++) {
		switch(i) {
			case 0:
				std::cout << "Clubs: ";
				break;
			case 1:
				std::cout << "Diamonds: ";
				break;
			case 2:
				std::cout << "Hearts: ";
				break;
			case 3:
				std::cout << "Spades: ";
				break;
		}

		for (int j = 0; j < stacks_[i].size(); j++){
			switch (stacks_[i][j]) {
				case 0:
					std::cout << "A";
					break;
				case 10:
					std::cout << "J";
					break;
				case 11:
					std::cout << "Q";
					break;
				case 12:
					std::cout << "K";
					break;
				default:
					std::cout << stacks_[i][j]+1;

			}
			if (j !=  stacks_[i].size()-1) std::cout << " ";
		}
		std::cout << "\n";
	}
}

std::set<std::string> Table::getLegalCards() {
	return legalCards_;
}

void Table::addToStacks(Card card) {
	if (!isLegalCard(card)) return;  //guard
	int suit = card.getSuit();

	//determines if adding to front or back of stack
	if (stacks_[suit].size() > 0 && card.getRank() < stacks_[suit][0]) {
		stacks_[suit].insert(stacks_[suit].begin(), card.getRank());
	}
	else {
		stacks_[suit].push_back(card.getRank());
	}
	updateLegalCards(card);
}

//recalculates legal card set after new card is played
void Table::updateLegalCards(Card card) { //only called if card is allowed
	int suit = card.getSuit();
	int rank = card.getRank();
	std::string cardName = card.getCardName(card.getRank(), card.getSuit());

	legalCards_.erase(cardName);
	//special case: 7S played opens all other 7's
	if (legalCards_.find("7S") == legalCards_.begin()) {
		legalCards_.insert("7C");
		legalCards_.insert("7D");
		legalCards_.insert("7H");
		legalCards_.insert("6S");
		legalCards_.insert("8S");
		legalCards_.erase("7S");
	}
	else if (rank == (7-1)) { //index of 7 is 1 less due to enum numeration
		legalCards_.insert(card.getCardName(Rank(card.getRank() - 1), card.getSuit()));
		legalCards_.insert(card.getCardName(Rank(card.getRank() + 1), card.getSuit()));
	}
	else if (rank == (13-1) || rank == (1-1)) {} //king and ace
	else if (rank < (7-1)) { //cards less than 7
		legalCards_.insert(card.getCardName(Rank(card.getRank() - 1), card.getSuit()));
	}
	else { //cards greater than 7
		legalCards_.insert(card.getCardName(Rank(card.getRank() + 1), card.getSuit()));
	}
}

//reinitializes legal cards and clears stacks
void Table::clearTable() {
	legalCards_.clear();
	legalCards_.insert("7S");
	for (int i = 0; i < 4; i++) stacks_[i].clear();
}
