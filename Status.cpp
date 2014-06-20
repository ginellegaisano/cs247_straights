#include "Status.h"
#include "Card.h"
#include <vector>
#include <set>
#include <iostream>

Status::~Status() {}
Status::Status() {}

int Status::isInHand(Card card, std::vector<Card*>& hand) {
	std::cout << "in hand " << hand.size() << "\n";
	for (int i = 0; i < hand.size(); i++) {
		std::cout << "in hand " << *hand[i] << "\n";

		// if (card.getSuit() == hand[i]->getSuit() && card.getRank() == hand[i]->getRank() ) return i;
		if (card == *(hand[i])) return i;
	}
	return -1;
}

void Status::play(Table& table, Card& card, std::vector<Card*>& hand) {
	try {
		int index = isInHand(card, hand);
		// std::cout <<"Status Play: " <<index << "\n";
		if (index == -1 || !table.isLegalCard(card)) throw 1;
		// std::cout <<"no throw\n";
		table.addToStacks(card);
		// std::cout <<"added\n";

		hand.erase(hand.begin() + index);
	}
	catch(int) {
		throw 1;
	}

}

void Status::discard(Table& table, Card& card, std::vector<Card*>& hand, std::vector<Card*>& discardPile) {
	try {
		int index = isInHand(card, hand);
		std::string cardName;
		std::set<std::string> legalMoves = table.getLegalCards();
		for (int i = 0; i < hand.size(); i++){
			cardName = hand[i]->getCardName(hand[i]->getRank(), hand[i]->getSuit());
			if (legalMoves.find(cardName) != legalMoves.end()) throw 0;			
		}

		if (index == -1) throw 1;

		discardPile.push_back(&card);
		hand.erase(hand.begin() + index);
	}
	catch(int e) {
		std::cout << e << std::endl;
		throw 1;
	}
}

