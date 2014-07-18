#include "Model.h"

#define CARD_COUNT 52

using namespace std;

Model::Model() {
	table = new Table();
}

Model::~Model() {
	for (int i = 0; i < 4; i++) delete players[i];

	delete table;

	for (int i = 0; i < 52; i++) delete cards_[i];
}
//shuffles the hards.
void Model::shuffle(int seed){
	int n = CARD_COUNT;

	srand48(seed);

	while (n > 1) {
		int k = (int)(lrand48() % n);
		--n;
		Card *c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
}

//initializes deck of cards with cards objects in order 
void Model::initializeDeck( bool players[4]) {
	for (int i = 0; i < 4; i++) {
		playerStat[i] = players[i];
		players[i] = new Player(players[i]);
	}
	for (int i = 0; i < 4; i++){
		Suit suit;
		switch (i) {
		case 0:
			suit = CLUB;
			break;
		case 1:
			suit = DIAMOND;
			break;
		case 2:
			suit = HEART;
			break;
		case 3:
			suit = SPADE;
			break;
		}
		for (int j = 0; j < 13; j++){
			switch (j) {
			case 0:
				cards_[(i * 13) + j] = new Card(suit, ACE);
				break;
			case 1:
				cards_[(i * 13) + j] = new Card(suit, TWO);
				break;
			case 2:
				cards_[(i * 13) + j] = new Card(suit, THREE);
				break;
			case 3:
				cards_[(i * 13) + j] = new Card(suit, FOUR);
				break;
			case 4:
				cards_[(i * 13) + j] = new Card(suit, FIVE);
				break;
			case 5:
				cards_[(i * 13) + j] = new Card(suit, SIX);
				break;
			case 6:
				cards_[(i * 13) + j] = new Card(suit, SEVEN);
				break;
			case 7:
				cards_[(i * 13) + j] = new Card(suit, EIGHT);
				break;
			case 8:
				cards_[(i * 13) + j] = new Card(suit, NINE);
				break;
			case 9:
				cards_[(i * 13) + j] = new Card(suit, TEN);
				break;
			case 10:
				cards_[(i * 13) + j] = new Card(suit, JACK);
				break;
			case 11:
				cards_[(i * 13) + j] = new Card(suit, QUEEN);
				break;
			case 12:
				cards_[(i * 13) + j] = new Card(suit, KING);
				break;
			}
		}
	}
}

//deals to hand to player and returns true if player has 7 of spades
bool Model::deal(int playerNum){
	vector<Card*> hand;
	bool firstPlayer = false;
	for (int j = 0; j < 13; j++){
		Card* curCard = cards_[playerNum * 13 + j];
		string cardName = curCard->getCardName(curCard->getRank(), curCard->getSuit());
		(hand).push_back(curCard);
		if (cardName == "7S") firstPlayer = true;
	}

	players[playerNum]->setHand(hand);

	return firstPlayer;
}

bool Model::finish(){
	int curScore;
	if (cardsPlayed == 52) finished = true;
	winner[0] = players[0]->getScore();
	for (int i = 0; i < 4; i++){
		curScore = players[i]->getScore();
		if (curScore < winner[0]){
			winner[0] = i;
		}
		else if (curScore == winner[0]){
			winner.push_back(i);
		}

		if (curScore >= 80) finished = true;
	}
	return finished;
}

std::vector <int> Model::getWinner(){
	return winner;
}

//cleans up table
void Model::finishRound(){
	table->clearTable();

}

//deals hands and returns the starting player
int Model::newGame(int seed) {
	finished = false;
	shuffle(seed);
	int startingPlayer;
	for (int i = 0; i < 4; i++){
		if (deal(i)) startingPlayer = i;
	}
	currentPlayer_ = startingPlayer;
	return startingPlayer;
}

std::vector <std::pair <int, int> > Model::getHand(){
	std::vector <std::pair <int, int> > ret;
	int suit;
	int rank;
	std::pair<int, int> cardInt;
	std::vector<Card*>* handCard = players[currentPlayer_]->getHand;
	for (int i = 0; i < (*handCard).size(); i++){
		suit = (*handCard)[i]->getSuit();
		rank = (*handCard)[i]->getRank();
		cardInt.first = (int) suit;
		cardInt.second = (int) rank;
		ret.push_back(cardInt);
	}
}

std::vector <int> Model::getLegalMoves(){
	std::vector<int> ret;
	std::vector<Card*>* handCard = players[currentPlayer_]->getHand;
	for (int i = 0; i < (*handCard).size(); i++){
		if (table->isLegalCard((*(*handCard)[i]))) ret.push_back(i);
	}
	return ret;
}

std::vector <std::pair <int, int> > Model::getTable(){
	std::vector <std::pair <int, int> > ret;
	std::pair<int, int> card;
	std::vector<int> tableVector;
	for (int i = 0; i < 4; i++){
		tableVector = table->getStacks(i);
		for (int j = 0; j < tableVector.size(); j++){
			card.first = i;
			card.first = tableVector[j];
			ret.push_back(card);
		}
	}
	return ret;
}



int Model::getScore(){
	return players[currentPlayer_]->getScore();
}
void Model::makeMove(int a=-1){
	cardsPlayed++;
	std::vector<Card*>* hand = players[currentPlayer_]->getHand;
	Card* c;
	if (a!=-1)	c = (*hand)[a];
	else c = (*hand)[0];
	players[currentPlayer_]->makeMove(c,*table);
	currentPlayer_ = (currentPlayer_ + 1) % 4;
}

bool Model::getPlayerType(){
	return playerStat[currentPlayer_];
}

int Model::getPlayerNum(){
	return currentPlayer_;
}

void Model::ragequit(){
	playerStat[currentPlayer_] = false;
}