#include "Model.h"

#define CARD_COUNT 52


using namespace std;

//constructor
Model::Model() {
	cardsPlayed = 0;
	table = new Table();
}

//desctructor
Model::~Model() {
	for (int i = 0; i < PLAYER_COUNT; i++) delete players[i];

	delete table;

	for (int i = 0; i < CARD_COUNT; i++) delete cards[i];
}

//shuffles the hands.
void Model::shuffle(long seed){
	cout<<"shuffled\n";
	int n = CARD_COUNT;

	srand48(seed);

	while (n > 1) {
		int k = (int)(lrand48() % n);
		--n;
		Card *c = cards[n];
		cards[n] = cards[k];
		cards[k] = c;
	}
}

//initializes deck of cards with cards objects in order. intializes the players.
void Model::initializeDeck( bool player_[PLAYER_COUNT]) {

	std::cout << "Initializing deck...\n";
	for (int i = 0; i < PLAYER_COUNT; i++) {
		playerStat[i] = player_[i];
		players[i] = new Player(playerStat[i]);
	}
	for (int i = 0; i < PLAYER_COUNT; i++){
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
				cards[(i * 13) + j] = new Card(suit, ACE);
				break;
			case 1:
				cards[(i * 13) + j] = new Card(suit, TWO);
				break;
			case 2:
				cards[(i * 13) + j] = new Card(suit, THREE);
				break;
			case 3:
				cards[(i * 13) + j] = new Card(suit, FOUR);
				break;
			case 4:
				cards[(i * 13) + j] = new Card(suit, FIVE);
				break;
			case 5:
				cards[(i * 13) + j] = new Card(suit, SIX);
				break;
			case 6:
				cards[(i * 13) + j] = new Card(suit, SEVEN);
				break;
			case 7:
				cards[(i * 13) + j] = new Card(suit, EIGHT);
				break;
			case 8:
				cards[(i * 13) + j] = new Card(suit, NINE);
				break;
			case 9:
				cards[(i * 13) + j] = new Card(suit, TEN);
				break;
			case 10:
				cards[(i * 13) + j] = new Card(suit, JACK);
				break;
			case 11:
				cards[(i * 13) + j] = new Card(suit, QUEEN);
				break;
			case 12:
				cards[(i * 13) + j] = new Card(suit, KING);
				break;
			}
		}
	}
}

//deals to hand to player and returns true if player has 7 of spades
bool Model::deal(int playerNum){
	vector<Card*> hand;
	bool firstPlayer = false;
	cout<<"dealing...\n";
	for (int j = 0; j < MAX_HAND_COUNT; j++){
		Card* curCard = cards[playerNum * 13 + j];
		string cardName = curCard->getCardName(curCard->getRank(), curCard->getSuit());
		(hand).push_back(curCard);
		if (cardName == "7S") firstPlayer = true;
	}
	players[playerNum]->setHand(hand);

	return firstPlayer;
}

//returns true if the game is finished (all 52 cards played
//and there is a player with score of >80)
//calculates the winner (player with lowest score)
bool Model::gameDone(){
	int curScore = 0;
	if (cardsPlayed == 52) finished = true;
	players[0]->calculateScore();
	winner.clear();
	curScore = players[0]->getScore();
	winner.push_back(1);
	for (int i = 1; i < PLAYER_COUNT; i++){
		players[i]->calculateScore();
		curScore = players[i]->getScore();
		if (curScore < players[winner[0]-1]->getScore()){
			winner[0] = i+1;
		}
		else if (curScore == players[winner[0]-1]->getScore()){
			winner.push_back(i+1);
		}

		if (curScore >= 80) finished = true;
	}
	return finished;
}

//returns true if the round has been finished (52 cards played)
bool Model::finish(){
	bool finished = (cardsPlayed == 52);
	if (finished){
		table->clearTable();
		for (int i =0; i < PLAYER_COUNT; i ++){
			players[i]->calculateScore();
			players[i]->clearCards();
		}
		cardsPlayed = 0;
	}

	return finished;
}

//returns the vector of winners
std::vector <int> Model::getWinner(){
	return winner;
}


//deals hands and returns the starting player
int Model::newGame(int seed) {
	finished = false;
	shuffle(seed);
	table->clearTable();

	int startingPlayer;
	for (int i = 0; i < PLAYER_COUNT; i++){
		if (deal(i)) startingPlayer = i;
	}
	currentPlayer_ = startingPlayer;
	notify();
	return startingPlayer;
}

//resets player hands to 0.
void Model::resetPlayerScores(){
	cardsPlayed = 0;
	for (int i = 0; i < PLAYER_COUNT; i++)
		players[i]->newGame();
}


std::vector <std::pair <int, int> > Model::getHand(){
	std::vector <std::pair <int, int> > ret;
	int suit;
	int rank;
	std::pair<int, int> cardInt;
	// cout<<"got into model->getHand\n";
	std::vector<Card*>* handCard = players[currentPlayer_]->getHand();
	for (int i = 0; i < (*handCard).size(); i++){
		suit = (*handCard)[i]->getSuit();
		rank = (*handCard)[i]->getRank(); 
		cardInt.first = (int) suit;
		cardInt.second = (int) rank;
		ret.push_back(cardInt);
	}	
	return ret;
}

std::vector <int> Model::getLegalMoves(){
	std::vector<int> ret;
	std::vector<Card*>* handCard = players[currentPlayer_]->getHand();
	for (int i = 0; i < (*handCard).size(); i++){
		if (table->isLegalCard((*(*handCard)[i]))) ret.push_back(i);
	}
	return ret;
}

std::vector <std::pair <int, int> > Model::getTable(){
	std::vector <std::pair <int, int> > ret;
	std::pair<int, int> card;
	std::vector<int> tableVector;
	for (int i = 0; i < PLAYER_COUNT; i++){
		tableVector = table->getStacks(i);
		for (int j = 0; j < tableVector.size(); j++){
			card.first = i;
			card.second = tableVector[j];
			ret.push_back(card);
		}
	}
	return ret;
}



int Model::getScore(int playerNum){
	return players[playerNum]->getScore();
}

std::string Model::getCardName(int cardNum){
	std::cout << "in get card name with " << cardNum <<"\n";
	Card* card = (*players[currentPlayer_]->getHand())[cardNum];
	std:: cout << "card " << card->getCardName(card->getRank(), card->getSuit()) <<std::endl;
	string ret = card->getCardName(card->getRank(), card->getSuit());
	return ret;
}

std::string Model::getLastPlayedCard() {
	if (cardsPlayed == 0)
		return "";

	string ret;
	if (lastPlayedCard_.first) ret += "Played ";
	else ret += "Discarded ";

	ret += cards[0]->getCardName(lastPlayedCard_.second.first, lastPlayedCard_.second.second);
	return ret;
}


void Model::makeMove(int a=-1){
	cardsPlayed++;
	pair <bool, pair <Rank, Suit> > currentCard;
	if (getLegalMoves().size()!=0) currentCard.first = 1;
	else currentCard.first = 0;
	std::vector<Card*>* hand = players[currentPlayer_]->getHand();
	Card* c;
	if (a!=-1){
		c = (*hand)[a];
	}else{
		if (getLegalMoves().size()!=0){
			c = (*hand)[(getLegalMoves()[0])];
		}
		else 
			c = (*hand)[0];
	}
		currentCard.second.first = c->getRank();
		currentCard.second.second = c->getSuit();

	lastPlayedCard_ = currentCard;
	players[currentPlayer_]->makeMove(c,*table);
	currentPlayer_ = (currentPlayer_ + 1) % PLAYER_COUNT;
	notify();
}

bool Model::getPlayerType(){
	return playerStat[currentPlayer_];
}

int Model::getPlayerNum(){
	return currentPlayer_;
}

void Model::ragequit(){
	playerStat[currentPlayer_] = false;
	notify();
	
}

bool Model::isLegalMoves(int i){
	std::vector<Card*>* hand = players[currentPlayer_]->getHand();
	Card*c = (*hand)[i];
	return table->isLegalCard(*c);
}

int Model::getDiscard(int playerNum){
	return players[playerNum]->getDiscardPileSize();
}