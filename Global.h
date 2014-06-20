#ifndef _GLOBAL_
#define _GLOBAL_

#include "Card.h"
#include <iostream>
#include <vector>

extern Card *cards_[52];

void printDeck();

void printCards(std::vector<Card*>& cards);

#endif