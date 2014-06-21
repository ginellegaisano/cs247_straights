#include "Global.h"

Card *cards_[52];

void printDeck() {
	for (int i = 0; i < 52; i++){
		std::cout << *cards_[i];
		if ((i+1) % 13 == 0) std::cout << std::endl;
		else std::cout << " ";
	}
	std::cout << std::endl;
}

//prints any vector of cards (hand, discard pile, legal cards)
void printCards(std::vector<Card*>& cards) {
	for (int i = 0; i < cards.size(); i++) {
		std::cout << *(cards[i]);
		if (i != (cards.size()-1)) std::cout << " ";
	}
	std::cout << "\n";

}

