#include "Computer.h"
#include "Status.h"
#include "Card.h"
#include "Command.h"
#include "Table.h"
#include <vector>
#include <iostream>
#include <set>
#include "Global.h"

Command Computer::makeMove(Table& table, std::vector<Card*>& hand, std::vector<Card*>& discardPile){
	Command command;

	//checks if there is a legal play in hand 
	for (int i=0; i < hand.size(); i++){
		Card *card = hand[i];
		if (table.isLegalCard(*card)){
			//plays first legal card found
			play(table, *card, hand);
			command.type = PLAY;
			command.card = *card;
			return command;
		}
	}
	//if no legal play found, discards first card in hand
	command.type = DISCARD;
	command.card = *(hand[0]);
	discard (table, *(hand[0]), hand, discardPile);

	return command;

}

Computer::Computer() {}
Computer::~Computer() {}