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
		//checks if card is in hand
		int index = isInHand(card, hand);
		std::cout << "is in hand: " << index << std::endl;
		if (index == -1 || !table.isLegalCard(card)) throw 1;
		table.addToStacks(card);

		hand.erase(hand.begin() + index);
	}
	catch (int) {
		throw 1; //taken care of in makeMove
	}

}

void Status::discard(Table& table, Card& card, std::vector<Card*>& hand, std::vector<Card*>& discardPile) {
	try {
		//checks if card is in hand
		int index = isInHand(card, hand);
		std::string cardName;

		//checks if player has any legal moves
		std::set<std::string> legalMoves = table.getLegalCards();
		for (int i = 0; i < hand.size(); i++){
			cardName = hand[i]->getCardName(hand[i]->getRank(), hand[i]->getSuit());
			if (legalMoves.find(cardName) != legalMoves.end()) throw 2;
		}

		if (index == -1) throw 1;

		discardPile.push_back(&card);
		hand.erase(hand.begin() + index);
	}
	catch (int e) {
		std:: cout << "error code: " << e << std::endl;
		throw e;
	}
}

void Status::makeMove(Card* card, Table& table, std::vector<Card*>& hand, std::vector<Card*>& discardPile){
		std::cout << "in computer make move: " + card->getCardName(card->getRank(), card->getSuit()) << std::endl;
	//checks if there is a legal play in hand 
	if (table.isLegalCard(*card)){
	std::cout << "in computer play\n";

		//plays first legal card found
		play(table, *card, hand);
	}else{
	std::cout << "in computer discard\n";

		//if no legal play found, discards first card in hand
		discard(table, *card, hand, discardPile);
	}
}