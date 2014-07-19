#include "Computer.h"
#include "Status.h"
#include "Card.h"
#include "Table.h"
#include <vector>
#include <iostream>
#include <set>

void Computer::makeMove(Card* card, Table& table, std::vector<Card*>& hand, std::vector<Card*>& discardPile){
	std::cout << "in computer make move\n";
	//checks if there is a legal play in hand 

	if (table.isLegalCard(*card)){
		//plays first legal card found
		play(table, *card, hand);
	}else{
		//if no legal play found, discards first card in hand
		discard(table, *card, hand, discardPile);
	}
}

Computer::Computer() {}
Computer::~Computer() {}