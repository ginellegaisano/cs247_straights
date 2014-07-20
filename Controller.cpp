#include "Controller.h"
#include "Model.h"
#include <iostream>

//constructor
Controller::Controller(Model *m) {
	model_ = m; 
}

//called once when window is opened. initializes the deck. Creates a new game
void Controller::Controller::initializeDeck(std::vector<bool> players) {
	bool array[PLAYER_COUNT];
	for (int i = 0; i < players.size(); i++){
		array[i] = players[i];
	}
	model_->initializeDeck(array);
	model_->newGame(0);
}

//functions associated with each button click.
void Controller::startNewGame(int seedNum){
	model_->newGame(seedNum);
}
void Controller::rageQuit(){
	model_->ragequit();
}
void Controller::quitGame(){
	model_->finish();
}
//returns whether or not a card can be played.
bool Controller::playCard(int cardNum){
	if(cardNum !=-1 && model_->getLegalMoves().size()!=0 && !model_->isLegalMoves(cardNum)){
		return false;
	}
	std::cout<<"before model makemove\n";
	model_->makeMove(cardNum);
}

std::vector<std::pair<int, int> > Controller::getTable(){
	return model_->getTable();
}

std::vector<std::pair<int, int> > Controller::getHand(){
	return model_->getHand();
}

//get statements. 
int Controller::getPlayerNum(){
	return model_->getPlayerNum();
}
std::vector<int> Controller::getWinner(){
	return model_->getWinner();
}
std::vector<int> Controller::getLegalMoves(){
	return model_->getLegalMoves();
}
bool Controller::getPlayerType(){
	return model_->getPlayerType();
}
int Controller::getDiscard(int i){
	return model_->getDiscard(i);
}

std::string Controller::getLastPlayedCard() {
	return model_->getLastPlayedCard();
}

int Controller::getScore(int playerNum){
	return model_->getScore(playerNum);
}

//determines if the round is finished
bool Controller::finished(){
	return model_->finish();
}
//determines if the game is finished (a player has more than 80 points)
bool Controller::gameDone(){
	return model_->gameDone();
}
//resets all player scores to 0.
void Controller::resetPlayerScores(){
	model_->resetPlayerScores();
}
