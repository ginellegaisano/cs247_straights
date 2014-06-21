#include "Table.h"
#include <set>
#include "Card.h"
#include <vector>
#include <iostream>

Table::Table(){
	legalCards_.insert("7S");
}
Table::~Table(){}

bool Table::isLegalCard(Card card) {
	// std::cout << "Legal cards: " << legalCards_.size() << "\n";
	// if (legalCards_.size() == 0) {
	// 	if (card.getCardName(card.getRank(), card.getSuit()) != "7S") {
	// 		return false;
	// 	}
	// 	return true;
	// }
	// else {
		//need to check if card is in legalCards, right?
		if (legalCards_.find(card.getCardName(card.getRank(), card.getSuit())) != legalCards_.end()) {
			return true;
		}
		else {
			return false;
		}
	// }
}

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
	if (!isLegalCard(card)) return;
	int suit = card.getSuit();
	if (stacks_[suit].size() > 0 && card.getRank() < stacks_[suit][0]) {
		stacks_[suit].insert(stacks_[suit].begin(), card.getRank());
	}
	else {
		stacks_[suit].push_back(card.getRank());
	}
	updateLegalCards(card);
}

void Table::updateLegalCards(Card card) { //only called if card is allowed
	int suit = card.getSuit();
	int rank = card.getRank();
	std::string cardName = card.getCardName(card.getRank(), card.getSuit());

	legalCards_.erase(cardName);
	// std::cout << (legalCards_.find("7S") == legalCards_.end()) << std::endl;
	if (legalCards_.find("7S") == legalCards_.begin()) {
		legalCards_.insert("7C");
		legalCards_.insert("7D");
		legalCards_.insert("7H");
		legalCards_.insert("6S");
		legalCards_.insert("8S");
		legalCards_.erase("7S");
	}
	else if (rank == (7-1)) { //index of 7 is 1 less
		legalCards_.insert(card.getCardName(Rank(card.getRank() - 1), card.getSuit()));
		legalCards_.insert(card.getCardName(Rank(card.getRank() + 1), card.getSuit()));
	}
	else if (rank == (13-1) || rank == (1-1)) {} //king and ace
	else if (rank < (7-1)) {
		legalCards_.insert(card.getCardName(Rank(card.getRank() - 1), card.getSuit()));
	}
	else {
		legalCards_.insert(card.getCardName(Rank(card.getRank() + 1), card.getSuit()));
	}
}

void Table::clearTable() {
	legalCards_.clear();
	legalCards_.insert("7S");
	for (int i = 0; i < 4; i++) stacks_[i].clear();
}
