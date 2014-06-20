#include "Player.h"
#include "Card.h"
#include "Command.h"
#include "Status.h"
#include "Human.h"
#include "Computer.h"
#include <vector>
#include "Global.h"

void Player::printDiscards() {
	printCards(*discardPile_);
}

Player::Player(bool isHuman, int playerNumber) {
	if (isHuman)
		status_ = new Human();
	else
		status_ = new Computer();

	discardPile_ = new std::vector<Card*>();
	score_ = 0;
	playerNumber_ = playerNumber;
}

Player::~Player() {
	delete hand_;
	delete discardPile_;
	delete status_;
}

int Player::getScore() {
	return score_;
}

void Player::calculateScore() {
	for (int i = 0; i < discardPile_->size(); i++) 
		score_ += 1 + (*discardPile_)[i]->getRank();
}

void Player::setHand(std::vector<Card*>& hand){
	hand_ = &hand;
}

Command Player::makeMove(Table& table) {
	return status_->makeMove(table, *hand_, *discardPile_, playerNumber_);
	
}