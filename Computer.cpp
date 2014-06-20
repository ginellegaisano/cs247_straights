#include "Computer.h"
#include "Status.h"
#include "Card.h"
#include "Command.h"
#include "Table.h"
#include <vector>
#include <iostream>
#include <set>
#include "Global.h"

Command Computer::makeMove(Table& table, std::vector<Card*>& hand, std::vector<Card*>& discardPile, int playerNum){
	Command command;
	std::cout << "Hand: ";
	printCards(hand);
	table.printStacks();
	for (int i=0; i < hand.size(); i++){
		Card *card = hand[i];
		if (table.isLegalCard(*card)){
			play(table, *card, hand);
			command.type = PLAY;
			command.card = *card;
			return command;
		}
	}
	discard (table, *hand[0], hand, discardPile);
	command.type = DISCARD;
	command.card = *hand[0];
	return command;

}

Computer::Computer() {}
Computer::~Computer() {
	std::cout << "deleting computer\n";
}