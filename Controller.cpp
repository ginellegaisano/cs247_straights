#include "Controller.h"
#include "Model.h"
#include <iostream>

Controller::Controller(Model *m) {
	model_ = m; 
}

//called once when window is opened
void Controller::Controller::initializeDeck(std::vector<bool> players) {
	bool array[4];
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
bool Controller::playCard(int cardNum){
	std::cout<<"cardNum\n";
	if(cardNum !=-1 && model_->getLegalMoves().size()!=0 && !model_->isLegalMoves(cardNum)){
		return false;
	}
	std::cout<<"before mmodel makemove\n";
	model_->makeMove(cardNum);
}

std::vector<std::pair<int, int> > Controller::getTable(){
	return model_->getTable();
}

std::vector<std::pair<int, int> > Controller::getHand(){
	return model_->getHand();
}

void Controller::finishRound(){} //dont know if i should remove this...

//get statements. information?
int Controller::getPlayerNum(){
	return model_->getPlayerNum();
}

std::vector<int> Controller::getLegalMoves(){
	return model_->getLegalMoves();
}
bool Controller::getPlayerType(){
	return model_->getPlayerType();
}
int Controller::getScore(){}
bool Controller::finished(){}