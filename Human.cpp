#include "Human.h"
#include "Status.h"
#include "Card.h"
#include "Table.h"

#include <vector>
#include <iostream>
#include <set>

Human::Human() {}
Human::~Human() {}

void Human::makeMove(Card* card,Table& table, std::vector<Card*>& hand, std::vector<Card*>& discardPile) { //print hand, play, discard, quit
	if (table.isLegalCard(*card)){
		//plays first legal card found
		play(table, *card, hand);
	}
	else{
		//if no legal play found, discards first card in hand
		discard(table, *(hand[0]), hand, discardPile);
	}
}