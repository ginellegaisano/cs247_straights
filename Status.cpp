#include "Status.h"
#include "Card.h"
#include <vector>
#include <set>
#include <iostream>

Status::~Status() {}
Status::Status() {}

int Status::isInHand(Card card, std::vector<Card*>& hand) {
	for (int i = 0; i < hand.size(); i++) {
		if (card == *(hand[i])) return i;
	}

	return -1;
}

void Status::play(Table& table, Card& card, std::vector<Card*>& hand) {
	try {
		int index = isInHand(card, hand);
		if (index == -1 || !table.isLegalCard(card)) throw 1;
		table.addToStacks(card);

		hand.erase(hand.begin() + index);
	}
	catch(int) {
		throw 1;
	}

}

void Status::discard(Table& table, Card& card, std::vector<Card*>& hand, std::vector<Card*>& discardPile) {
	try {
		// std::cout << "Discard\n";
		int index = isInHand(card, hand);
		std::string cardName;
		// std::cout << "index of isInHand: " << index << std::endl;
		std::set<std::string> legalMoves = table.getLegalCards();
		for (int i = 0; i < hand.size(); i++){
			cardName = hand[i]->getCardName(hand[i]->getRank(), hand[i]->getSuit());
			// std::cout << cardName << std::endl;
			if (legalMoves.find(cardName) != legalMoves.end()) throw 2;
		}

		if (index == -1) throw 1;

		discardPile.push_back(&card);
		hand.erase(hand.begin() + index);
	}
	catch(int e) {
		throw e;
	}
}

