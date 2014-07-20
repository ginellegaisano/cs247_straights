#include "View.h"
#include <unistd.h>

namespace {

	string intToString(int a){
		stringstream b;
		b << a;
		return b.str();
	}

}

View::View(Controller *controller, Model *model): controller_(controller), model_(model),
				V(false,0) , Hmenu(true,0) , Hgame(false,0) , 
				Vdialogbox(false,0) , Vplay(false,1) , Hspades(true,1),	
				Hdiamonds(true,1) ,Hclubs(true,1) , Hhearts(true,1) ,
				HplayersBox(true,0) ,quitGame("Quit Game"),
				dialogButton("Enter"), dialogCounter(0),
				newGame("New Game with seed number:" ) ,
				dialogBoxLabel("Welcome!\n Player 1: Are you \nHuman(h) or Computer(c)?"), 
				HhandBox(false, 0) {

	//subscribing to model
	model_->subscribe(this);

	//setting the text for seedNum
	

	seedNum.set_text("0");

	//adding top menu bar
	Hmenu.add(newGame);
	Hmenu.add(seedNum);
	Hmenu.add(quitGame);

	V.add(Hmenu);

	//adding message box
	dialogBoxEntry.set_text("");
	dialogBoxLabel.set_size_request(160, 400);
	dialogBoxLabel.set_justify(Gtk::JUSTIFY_FILL);
	dialogBoxLabel.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);

	Vdialogbox.add(dialogBoxLabel);
	Vdialogbox.add(dialogBoxEntry);
	Vdialogbox.add(dialogButton);
	Hgame.add(Vdialogbox);
	

	//initializing the images

	// nullImage = new Gtk::Image(deck.getNullCardImage());

	for (int i =0; i < 4; i ++){
		for (int k = 0; k < 13; k ++){
			Faces_ f = (Faces_) k;
			Suits_ s = (Suits_) i;
			Glib::RefPtr<Gdk::Pixbuf> *b = new Glib::RefPtr<Gdk::Pixbuf>( deck.getCardImage(f,s));

			cardImages[i][k] = (b);
			tableImages[i][k]= new Gtk::Image(deck.getNullCardImage());
			switch(i) {
				case 0:
					Hclubs.add(*tableImages[i][k]);break;
				case 1:
					Hdiamonds.add(*tableImages[i][k]);break;
				case 2:
					Hhearts.add(*tableImages[i][k]);break;
				case 3:
					Hspades.add(*tableImages[i][k]);break;
			}

		}
	}
	// Glib::RefPtr<Gdk::Pixbuf> b = deck.getCardImage(QUEEN,HEART);
	// tableImages[0][1]->set(*cardImages[2][12]);

	Vplay.add(Hclubs);
	Vplay.add(Hdiamonds);
	Vplay.add(Hhearts);
	Vplay.add(Hspades);

	//4 plays information fields. 
	for (int i = 0; i < PLAYER_COUNT; i ++){
		playerBoxes[i] = new Gtk::VBox(false, 0);
		scores[i].set_label("Score: 0");
		names[i].set_label("Player " + intToString(i+1));
		discards[i].set_label("Discard: 0");
		ragequits[i].set_label("RageQuit!!");
		 
		playerBoxes[i]->add(names[i]);
		playerBoxes[i]->add(discards[i]);
		playerBoxes[i]->add(scores[i]);
		playerBoxes[i]->add(ragequits[i]);

		ragequits[i].signal_clicked().connect( sigc::bind<int>( sigc::mem_fun(*this, &View::onRageQuitButtonClicked), i+1));

		ragequits[i].set_sensitive(false);
		HplayersBox.add(*playerBoxes[i]);
		// playerInfo[i] = new PlayerBox(i+1);
		// HplayersBox.add(*playerInfo[i]);
	}
	Vplay.add(HplayersBox);
	
	//setting player hand test
	for (int i = 0; i < MAX_HAND_COUNT; i++) {
		handImages[i] = new Gtk::Image(deck.getNullCardImage());
		// handImages[i]->set(*cardImages[0][i]);
		handButtons[i].set_image(*handImages[i]);
		HhandBox.add(handButtons[i]);

		//connects event handlers

	}

	Vplay.add(HhandBox);

	Hgame.add(Vplay);
	V.add(Hgame);

	newGame.signal_clicked().connect( sigc::mem_fun( *this, &View::onNewGameButtonClicked ) );
	quitGame.signal_clicked().connect( sigc::mem_fun( *this, &View::onQuitButtonClicked ) );
	dialogButton.signal_clicked().connect( sigc::mem_fun( *this, &View::onDialogButtonClicked ) );
	
	frame.add(V);
	add(frame);

	set_size_request(1000, 500);
	set_resizable (FALSE);
	show_all();

	Hmenu.hide();
}

void View::onDialogButtonClicked(){
	string dialogMessage = dialogBoxLabel.get_label();
	if (dialogBoxEntry.get_text() == "h" || dialogBoxEntry.get_text() == "c") {
		dialogMessage += "\n" + dialogBoxEntry.get_text() + "\n";
		if (dialogBoxEntry.get_text() == "h")
			playerStatus.push_back(true);
		else
			playerStatus.push_back(false);
	}
	else
		dialogMessage += "\n" + dialogBoxEntry.get_text() + " is invalid\n";

	if (playerStatus.size() != PLAYER_COUNT) {
		dialogMessage += "Player " + intToString(playerStatus.size()+1) + ": Are you \nHuman(h) or Computer(c)?";
		dialogBoxEntry.set_text("");
		dialogBoxLabel.set_text(dialogMessage);
	}
	else {
		//give PlayerStatus to controller
		dialogBoxLabel.set_text("Welcome to the game.");
		Hmenu.show_all();

		controller_->initializeDeck(playerStatus);
		for (int i = 0; i < MAX_HAND_COUNT; i++)
			handButtons[i].signal_clicked().connect( sigc::bind<int>( sigc::mem_fun(*this, &View::onCardButtonClicked), i));

		dialogBoxEntry.hide();
		dialogButton.hide();
		playerStatus.clear();
	}

	

}

void View::onNewGameButtonClicked(){//new name
	cout<<(atoi(seedNum.get_text().c_str()))<<endl;
	clearTable();
	dialogCounter = 123;
	updateDialogBox("Welcome to the game.");
	controller_->resetPlayerScores();
	controller_->startNewGame(atoi(seedNum.get_text().c_str()));
	setHandButtonsStatus(true);
	// updateDialogBox(seedNum.get_text());
}

void View::onQuitButtonClicked(){
	updateDialogBox("QUITTTT");
	Gtk::Main::quit();
}

void View::onRageQuitButtonClicked(int playerNum){
	vector< pair<int, int> > hand;
	updateDialogBox(intToString(playerNum)  + " has ragequitted.");
	setHand(hand);
	controller_->rageQuit();
}

void View::onCardButtonClicked(int cardNum){
	string message;
	bool mustDiscard = (controller_->getLegalMoves().size() == 0);
	// dialogBoxLabel.set_label(dialogBoxLabel.get_label() + "\n" + controller_->getCardName(cardNum));
	bool played = controller_->playCard(cardNum);
	// cout << "played = " << played << endl;
	if (!played)  {
		message += "Invalid Card";
		updateDialogBox( message);
	}

}

View::~View() {
	model_->unsubscribe(this);
	for (int i = 0; i < PLAYER_COUNT; i++) {
		delete playerBoxes[i];
		for (int j = 0; j < MAX_HAND_COUNT; j++) {
			delete cardImages[i][j];
			delete tableImages[i][j];
		}
	}
	for (int i = 0; i < MAX_HAND_COUNT ; i++) {
		delete handImages[i];
	}
	cout << "deleted View\n";
}

void View::update() {
	cout << "Updating\n";
	//update dialog box
		//if end game, print scores to dialog box
		//get endGame
			//if endGame, print winner, clear everything and return
	bool isFinished = controller_->finished();
	string lastCard = controller_->getLastPlayedCard();
	if (lastCard != "")
		updateDialogBox(lastCard);

	bool gameDone = false;
	cout << isFinished << endl;
	if (isFinished) { //round is done
		cout << "is finished\n";
		clearTable();

		dialogCounter = 100;
		updateDialogBox("Round is done!");
		updateDialogBox("Beginning new round.");
		gameDone = controller_->gameDone();
		if (gameDone) {
			cout <<"Game is done!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
			dialogCounter = 23213;
			vector <int > winners = controller_->getWinner();
			for (int i = 0; i < winners.size(); i++)
				updateDialogBox("Player " + intToString(winners[i]) + " wins!");
			//disable hand
			return;
		}
		controller_->startNewGame(atoi(seedNum.get_text().c_str()));
	}
	else if (!gameDone) {
		updateDialogBox("Player "  + intToString(controller_->getPlayerNum()+1) + "'s turn");
			//get player number
				//get player status (human or computer)
					//if computer, call play immediate
		cout << controller_->getPlayerNum() << " "  <<   !controller_->getPlayerType() <<endl;
		if (!controller_->getPlayerType()) {
			cout << "Computer playing\n";
			setHandButtonsStatus(false);

			controller_->playCard(-1);
		}
		//if human, get hand and update hand
		else {
			std::cout<<"before getting the hand\n";
			setHandButtonsStatus(true);
			vector <int> legalCards = controller_->getLegalMoves();

				// gtk_widget_modify_bg (GTK_WIDGET(handButtons[legalCards[i]]), GTK_STATE_NORMAL, &color);
			vector <pair<int, int> > hand = controller_->getHand();
			std::cout<<"after getHand\n";
			// for (int i = 0; i < 10; i++) //setting hand
			// 	hand.push_back(make_pair(2, 2));
			setHand(hand);
			cout << "legal moves: "<<controller_->getLegalMoves().size()  << endl;

			if (controller_->getLegalMoves().size() == 0) {
			cout << "legal moves: "<<controller_->getLegalMoves().size()  << endl;
				updateDialogBox("No legal moves ");
				updateDialogBox("Choose discard");
			}

		}
	}
	//Update table
	vector<pair<int, int > > tableCards_ = controller_->getTable();
	
	for (int i = 0; i < tableCards_.size(); i++)
		tableImages[tableCards_[i].first][tableCards_[i].second]->set(*cardImages[tableCards_[i].first][tableCards_[i].second]);
	
	//update player boxes
	//Update rageQuit buttons (disable when not player's turn)
	for (int i = 0; i < PLAYER_COUNT; i++) {
		scores[i].set_label("Score: " + intToString(controller_->getScore(i)));
		discards[i].set_label("Discard: " + intToString(controller_->getDiscard(i)));
		if (controller_->getPlayerNum() == i && controller_->getPlayerType()) 
			ragequits[i].set_sensitive(true);
		else 
			ragequits[i].set_sensitive(false);
	}
}

void View::setHand(vector<pair<int ,int> > hand) {
	for (int i = 0; i < hand.size(); i++) //setting hand
		handImages[i]->set(*cardImages[hand[i].first][hand[i].second]);
	for (int i = hand.size(); i < MAX_HAND_COUNT; i++) {
		handImages[i]->set(deck.getNullCardImage());
		handButtons[i].set_sensitive(false);
	}
}

void View::updateDialogBox(string message) {
	if (dialogCounter < 27) {
		message = dialogBoxLabel.get_text() + "\n" + message;
		dialogCounter++;
	}
	else {
		dialogCounter = 0;
	}

	dialogBoxLabel.set_label(message);
}

void View::setHandButtonsStatus(bool on) {
	for (int i = 0; i < MAX_HAND_COUNT; i++)
		handButtons[i].set_sensitive(on);

}

void View::clearTable() {
	for (int i = 0; i < PLAYER_COUNT; i++)
			for (int j = 0; j < 13; j++)
				tableImages[i][j]->set(deck.getNullCardImage());
}