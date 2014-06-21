#include "Game.h"

#define CARD_COUNT 52

using namespace std;

Game::Game() {
	table = new Table();
}

void Game::shuffle(){
	int n = CARD_COUNT;

	while ( n > 1 ) {
		int k = (int) (lrand48() % n);
		--n;
		Card *c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
}

//initializes deck of cards with cards objects in order 
void Game::initializeDeck() {
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
			switch(j) {
				case 0:
					cards_[(i*13) + j] = new Card(suit, ACE);
					break;
				case 1:
					cards_[(i*13) + j] = new Card(suit, TWO);
					break;
				case 2:
					cards_[(i*13) + j] = new Card(suit, THREE);
					break;
				case 3:
					cards_[(i*13) + j] = new Card(suit, FOUR);
					break;
				case 4:
					cards_[(i*13) + j] = new Card(suit, FIVE);
					break;
				case 5:
					cards_[(i*13) + j] = new Card(suit, SIX);
					break;
				case 6:
					cards_[(i*13) + j] = new Card(suit, SEVEN);
					break;
				case 7:
					cards_[(i*13) + j] = new Card(suit, EIGHT);
					break;
				case 8:
					cards_[(i*13) + j] = new Card(suit, NINE);
					break;
				case 9:
					cards_[(i*13) + j] = new Card(suit, TEN);
					break;
				case 10:
					cards_[(i*13) + j] = new Card(suit, JACK);
					break;
				case 11:
					cards_[(i*13) + j] = new Card(suit, QUEEN);
					break;
				case 12:
					cards_[(i*13) + j] = new Card(suit, KING);
					break;
			}
		}
	}
}

bool Game::deal(int playerNum){
	vector<Card*> hand;
	bool firstPlayer = false;
	for (int j = 0; j < 13; j++){
		Card* curCard = cards_[playerNum*13+j];
		string cardName = curCard->getCardName(curCard->getRank(), curCard->getSuit()); 
		(hand).push_back(curCard);
		if(cardName == "7S") firstPlayer = true;
	}

	players[playerNum]->setHand(hand);

	return firstPlayer;
}

void Game::endRound(){ //cleans up hand, discard pile, and calculates score
	table->clearTable();

}

void Game::quit (Player *players[4], Table* table) {
	for (int i = 0; i < 4; i++) delete players[i];
	
	delete table;

	for (int i = 0; i < 52; i++) delete cards_[i];
	
}
//plays rounds
// void Game::playGame(vector<Player*> players) {}

// //returns true if a player has a score of > 80
// bool playRound(vector<Player*> players) {} 


//at the beginning of every round, shuffle cards
void Game::playGame () {

	initializeDeck();

	for (int i = 1; i <= 4; i++) {
		char input;
		cout << "Is player " << i << " a human(h) or a computer(c)?\n>";
		cin >> input;
		// assert(!cin.fail() && (input == 'c' || input == 'C' || input == 'H' || input == 'h'));
		assert(!cin.fail() && (input == 'c' || input == 'h'));
		if (input == 'H' || input == 'h') {
			players[i-1] = new Player(true, i);
		} 
		else {
			players[i-1] = new Player(false, i);
		}
	}
	
	bool gameDone = false;
	int lowestScore = 234; //the highest score is 79 + 4*13 + 4*12 + 4*11 + 10 = 233


	while (!gameDone) {
		lowestScore = 234;
		shuffle(); //shuffle beginning of round

		int playerTurn;
		for (int i = 0; i < 4; i++) {
			if (deal(i)) playerTurn = i;
		}
		int cards = 0;
		cout << "A new round begins. It's player " << playerTurn+1 << "'s turn to play.\n";
			while (cards < 52) {
				Command command = players[playerTurn]->makeMove(*table); //can manipulate table if pass pointer reference
				
				if (command.type == RAGEQUIT) {
					players[playerTurn]->rageQuit();
					std::cout << "Player " << playerTurn+1 << " " << command << ". A computer will now take over.\n";

					command = players[playerTurn]->makeMove(*table);
				}
				else if (command.type == QUIT) {
					quit(players, table);
					return ;
				}
				
				if (command.type != DECK)	
					std::cout << "Player " << playerTurn+1 << " " << command << " " << command.card << ".\n";

				cards++;
				playerTurn = (playerTurn+1)%4;
			}

		for (int i = 0; i < 4; i++)  {
			int oldScore = players[i]->getScore();
			cout << "Player "<< i+1 << "'s discards: ";
			players[i]->printDiscards(); 
			cout << "Player "<< i+1 << "'s score: " << oldScore << " + ";
			players[i]->calculateScore(); //calculates new score
			cout << players[i]->getScore() - oldScore << " = " << players[i]->getScore() << endl;
			
			//always tracks for lowest score
			if (lowestScore > players[i]->getScore()) {
				lowestScore = players[i]->getScore();
			}
			
			if (players[i]->getScore() >= 80){
				gameDone = true;
		}
				players[i]->clearCards();

		}

		table->clearTable();

		// cin.ignore();
	}
	for (int i = 0; i < 4; i++)  
	if (lowestScore == players[i]->getScore()) 
		cout << "Player " << i+1 << " wins!\n";

	quit(players, table);

	

	//vector<Card*> playedCards_[4]; //clubs, diamonds, hearts, spade stacks played

}
