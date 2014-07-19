#include "Computer.h"
#include "Status.h"
#include "Card.h"
#include "Table.h"
#include <vector>
#include <iostream>
#include <set>

void Computer::makeMove(Card* card, Table& table, std::vector<Card*>& hand, std::vector<Card*>& discardPile){
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

Computer::Computer() {}
Computer::~Computer() {}