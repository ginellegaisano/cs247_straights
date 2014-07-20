#include "Player.h"
#include "Card.h"
#include "Status.h"
#include "Human.h"
#include "Computer.h"
#include <vector>
#include <iostream>

//clears discard pile
void Player::clearCards() {
	discardPile_->clear();
}

Player::Player(bool isHuman) {
	if (isHuman)
		status_ = new Human();
	else
		status_ = new Computer();

	hand_ = new std::vector<Card*>();
	discardPile_ = new std::vector<Card*>();
	score_ = 0;
}

Player::~Player() {
	delete hand_;
	delete discardPile_;
	delete status_;
}

int Player::getScore() {
	return score_;
}

std::vector<Card*>* Player::getHand(){
	return hand_;
}


//calculate score by summing the discard pile ranks
void Player::calculateScore() {
	for (int i = 0; i < discardPile_->size(); i++)
		score_ += 1 + (*discardPile_)[i]->getRank();
}

void Player::setHand(std::vector<Card*> hand){
	std::cout << "rer\n";
	(*hand_).clear();
	std::cout << "rer\n";

	for (int i = 0; i < 13; i++){
		std::cout<<i<<std::endl;
		(*hand_).push_back(hand[i]);}
}

//calls either Computer or Human make move. Returns command to 
//determine behaviour in Game
void Player::makeMove(Card* c, Table& table) {
	std::cout << "to status make move\n";
	return status_->makeMove(c, table, *hand_, *discardPile_);
}

void Player::rageQuit() {
	delete status_;
	status_ = new Computer();
}

int Player::getDiscardPileSize(){
	return discardPile_->size();
}

void Player::newGame(){
	score_ = 0;
}