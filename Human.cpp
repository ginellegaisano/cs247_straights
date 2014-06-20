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

bool Human::makeMove(Table& table, std::vector<Card*>& hand, std::vector<Card*>& discardPile, int playerNum) { //print hand, play, discard, quit
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
	while (!proceed) {
		try {
			std::cout << ">";
			Command command;
			std::cin >> command;
			int index = isInHand(command.card, hand);
			// std::cout << index << "\n";
			std::cin.ignore();

	// enum Type { PLAY, DISCARD, DECK, QUIT, RAGEQUIT, BAD_COMMAND };

			switch (command.type) {
				case PLAY:
					play(table, *hand[index], hand);
					std::cout << "Player " << playerNum << " plays " << command.card << ".\n";
					proceed = true;
					break;
				case DISCARD:
					discard(table, *hand[index], hand, discardPile);
					std::cout << "Player " << playerNum << " discards " << command.card << ".\n";
					proceed = true;

					break;
				case DECK:
					printDeck();
					break;
				case QUIT:
					return false;
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
	return true;
}