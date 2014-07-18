#include <gtkmm.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "DeckGUI.h"


using namespace std;

string intToString(int a){
	stringstream b;
	b << a;
	return b.str();
}

class View : public Gtk::Window{
	public:
		View();
		virtual ~View();
		void Update();
	protected:
		//signal handlers?
		virtual void onButtonClicked();
		virtual void onSeedNumButtonClicked();
		virtual void onQuitButtonClicked();
		virtual void onRageQuitButtonClicked(int);
		virtual void onCardButtonClicked(int);
		virtual void onDialogButtonClicked();
		virtual void update();
		//the pictures
		DeckGUI deck;
		Gtk::VBox V;
			Gtk::HBox Hmenu; //has the seed, input seed, quit
			Gtk::HBox Hgame;
				Gtk::VBox Vdialogbox;
					Gtk::Label dialogBoxLabel;
					Gtk::Button dialogButton;
					Gtk::Entry dialogBoxEntry;
				Gtk::VBox Vplay;
					Gtk::HBox Hdiamonds;
					Gtk::HBox Hclubs;
					Gtk::HBox Hspades;
					Gtk::HBox Hhearts;
					Gtk::HBox HplayersBox;
						Gtk::VBox *playerBoxes[4];
						// PlayerBox *playerInfo[4]  ;
					Gtk::HBox HhandBox;	//our hand and a rage quitbutton


		//hand view
		Gtk::Image *handImages[13];		//images for cards in hand
		Gtk::Button handButtons[13];	//buttons for cards in hand
		Gtk::Image *tableImages[4][13];	
		Glib::RefPtr<Gdk::Pixbuf> *cardImages[4][13];

		//Player boxes
			Gtk::Label scores[4];
			Gtk::Label names[4]; 
			Gtk::Label discards[4];
			Gtk::Button ragequits[4];

		Gtk::Frame frame;
		
		Gtk::Button quitGame;
		Gtk::Button newGame;
		Gtk::Entry seedNum;
		Gtk::Button ragequit;

		vector<bool> playerStatus;

};
View::View():	V(false,0) , Hmenu(true,0) , Hgame(false,0) , 
				Vdialogbox(false,0) , Vplay(false,1) , Hspades(true,1),	
				Hdiamonds(true,1) ,Hclubs(true,1) , Hhearts(true,1) ,
				HplayersBox(true,0) ,quitGame("Quit Game"),
				dialogButton("Enter"),
				newGame("New Game with seed number:" ) ,
				dialogBoxLabel("Welcome!\n Player 1: Are you \nHuman(h) or Computer(c)?"), HhandBox(false, 0) {

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
	

	//initializing the images. tableImages
	for (int i =0; i < 4; i ++){
		for (int k = 0; k < 13; k ++){
			Faces f = (Faces) k;
			Suits s = (Suits) i;
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
	for (int i = 0; i < 4; i ++){
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
	for (int i = 0; i < 13; i++) {
		handImages[i] = new Gtk::Image(deck.getNullCardImage());
		// handImages[i]->set(*cardImages[0][i]);
		handButtons[i].set_image(*handImages[i]);
		HhandBox.add(handButtons[i]);

		//connects event handlers
		handButtons[i].signal_clicked().connect( sigc::bind<int>( sigc::mem_fun(*this, &View::onCardButtonClicked), i));

	}

	Vplay.add(HhandBox);

	Hgame.add(Vplay);
	V.add(Hgame);

	newGame.signal_clicked().connect( sigc::mem_fun( *this, &View::onSeedNumButtonClicked ) );
	quitGame.signal_clicked().connect( sigc::mem_fun( *this, &View::onQuitButtonClicked ) );
	dialogButton.signal_clicked().connect( sigc::mem_fun( *this, &View::onDialogButtonClicked ) );
	
	frame.add(V);
	add(frame);

	set_size_request(1000, 500);
	set_resizable (FALSE);
	show_all();
}

// View::~View(){
// // 	for(int i = 0 ; i < 13; i++){
// // 		delete card[i];
// // 	}
// }

void View::onButtonClicked(){
	// some_button.set_label("beat.");
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

	if (playerStatus.size() != 4) 
		dialogMessage += "Player " + intToString(playerStatus.size()+1) + ": Are you \nHuman(h) or Computer(c)?";
	else {
		//give PlayerStatus to controller

		playerStatus.clear();
		dialogMessage = "Let's begin the game!";
		dialogBoxEntry.hide();
		dialogButton.hide();
	}
	dialogBoxEntry.set_text("");
	dialogBoxLabel.set_text(dialogMessage);
	

}

void View::onSeedNumButtonClicked(){
	dialogBoxLabel.set_label(dialogBoxLabel.get_label() + "\n" + seedNum.get_text());
}

void View::onQuitButtonClicked(){
	dialogBoxLabel.set_label(dialogBoxLabel.get_label() + "\n" + "QUITTTT");
	Gtk::Main::quit();
}

void View::onRageQuitButtonClicked(int playerNum){
	dialogBoxLabel.set_label(dialogBoxLabel.get_label() + "\n" + intToString(playerNum)  + " RAGEQUITTTT");
}

void View::onCardButtonClicked(int playerNum){
	//check if play is legal
	dialogBoxLabel.set_label(dialogBoxLabel.get_label() + "\nPlaying card " + intToString(playerNum) 	);
}

View::~View() {
	for (int i = 0; i < 4; i++) {
		cout << "deleting player box " << intToString(i) << endl;
		delete playerBoxes[i];
		for (int j = 0; j < 13; j++) {
		cout << "deleting cards " << intToString(j) << endl;
			delete cardImages[i][j];
			delete tableImages[i][j];
		}
	}
	for (int i = 0; i < 13 ; i++) {
		cout << "deleting hand " << intToString(i) << endl;
			delete handImages[i];
		}

}

void View::update() {
	//update dialog box
		//if end game, print scores to dialog box
		//get endGame
			//if endGame, print winner, clear everything and return

	//Update table

	//Update rageQuit buttons (disable when not player's turn)
	//ragequits[!playerNum].set_sensitive(false)

	//update player boxes
		//get player number
			//get player status (human or computer)
				//if computer, call play immediate
				//if human, get hand and update hand

}

int main(int argc, char* argv[]){
	Gtk::Main kit (argc, argv);
	View window;
	Gtk::Main::run( window );

	//hand view!

	return 0;
 }
