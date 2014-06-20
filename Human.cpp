#include "Human.h"
#include "Status.h"
#include "Card.h"
#include "Table.h"
#include "Command.h"
#include <vector>
#include <iostream>
#include <set>
#include "Global.h"

Human::Human() {}
Human::~Human() {}

Command Human::makeMove(Table& table, std::vector<Card*>& hand, std::vector<Card*>& discardPile, int playerNum) { //print hand, play, discard, quit
	std::vector<Card*> legalCards;
	bool proceed = false;
	for (int i = 0; i < hand.size(); i++) {
		if (table.isLegalCard(*hand[i])) {
			legalCards.push_back(hand[i]);
		}
	}
	table.printStacks();
	std::cout << "Your hand: ";
	printCards(hand); 
	std::cout << "Legal plays: ";
	printCards(legalCards);
	Command command;

	while (!proceed) {
		try {
			std::cout << ">";
			std::cin >> command;
			int index = isInHand(command.card, hand);
			// std::cout << index << "\n";

			switch (command.type) {
				case PLAY:
					if (index == -1 ) throw 0;

					play(table, *hand[index], hand);
					proceed = true;
					break;
				case DISCARD:
					if (index == -1 ) throw 0;

					discard(table, *hand[index], hand, discardPile);
					proceed = true;
					break;
				case DECK:
					printDeck();
					break;
				case QUIT:
					return command;
					break;
				case RAGEQUIT:
					proceed = true;
					break;
			}
		}
		catch(int) {
			std::cout<<"This is not a legal play.\n";
		}
	}
	return command;
}