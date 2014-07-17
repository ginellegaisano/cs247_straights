#include <gtkmm.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "DeckGUI.h"


using namespace std;
class HandBox: public Gtk::HBox{
public:
	HandBox(DeckGUI);
	virtual ~HandBox();
	void setHand(vector<Glib::RefPtr<Gdk::Pixbuf>*>);
	// Gtk::Button getButton(int);
private:
	Gtk::Button buttons[13];
	Gtk::Image* images[13];
	Gtk::Image* none_[13];
};

HandBox::HandBox(DeckGUI deck){	
	for (int i=0; i < 13; i ++){
		none_[i] = new Gtk::Image(deck.getNullCardImage());

		images[i] = none_[i];

		(buttons[i]).set_image(*images[i]);
	 	add(buttons[i]);
	}
}
// Gtk::Button HandBox::getButton(int num) {
// 	return buttons[num];
// }
HandBox::~HandBox(){
	delete []none_;
}
void HandBox::setHand(vector<Glib::RefPtr<Gdk::Pixbuf>*> cardImages){
	for (int i =0; i < cardImages.size(); i++){
		cout << i<< endl;
		images[i]->set(*cardImages[i]);
	}
	for (int i = cardImages.size(); i < 13; i++){
		images[i] = (none_[i]);
	}
}
class PlayerBox : public Gtk::VBox{
public:
	PlayerBox (int playerNumber);
	virtual ~PlayerBox();
	void setScore(int);
	void setDiscard(int);
	Gtk::Button getRagequit();
private:
	Gtk::Label score;
	Gtk::Label name; 
	Gtk::Label discard;
	Gtk::Button ragequit;
};

PlayerBox::PlayerBox(int playerNumber) : score("Score: 0"), name("Player "), discard("Discard: 0"), ragequit("RageQuit!!") {
	stringstream numberss;
	numberss << playerNumber;
	name.set_label("Player " + numberss.str());
	add(name);
	add(discard);
	add(score);
	add(ragequit);
}

PlayerBox::~PlayerBox(){
}

void PlayerBox::setScore(int score_){
	stringstream scoreSs;
	scoreSs << score_;
	score.set_label("Score: " + scoreSs.str());
}

void PlayerBox::setDiscard(int discard_){
	stringstream discardSs;
	discardSs << discard_;
	discard.set_label("Discard: " + discardSs.str());
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
		//the pictures
		DeckGUI deck; 
		Gtk::VBox V;
			Gtk::HBox Hmenu; //has the seed, input seed, quit
			Gtk::HBox Hgame;
				Gtk::VBox Vdialogbox;
					Gtk::Label dialogBoxLabel;
				Gtk::VBox Vplay;
					Gtk::HBox Hdiamonds;
					Gtk::HBox Hclubs;
					Gtk::HBox Hspades;
					Gtk::HBox Hhearts;
					Gtk::HBox HplayersBox;
						PlayerBox *playerInfo[4]  ;
					// Gtk::Hbox HandButtons;
					// Gtk::HBox HhandBox;	//our hand and a rage quitbutton
					HandBox handBox;
		//hand view
		Gtk::Image *handImages[13];
		Gtk::Button *handButtons[13];
		Gtk::Image *tableImages[4][13];
		Glib::RefPtr<Gdk::Pixbuf> *cardImages[4][13];
		Gtk::Image nothingImage;

		Gtk::Frame frame;
		
		Gtk::Button quitGame;
		Gtk::Button newGame;
		Gtk::Entry seedNum;
		Gtk::Button ragequit;

};
View::View():	V(false,0) , Hmenu(true,0) , Hgame(false,0) , 
				Vdialogbox(false,0) , Vplay(false,1) , Hspades(true,1),	
				Hdiamonds(true,1) ,Hclubs(true,1) , Hhearts(true,1) ,
				HplayersBox(true,0) ,quitGame("Quit Game"),
				newGame("New Game with seed number:" ) ,
				dialogBoxLabel("Welcome!"), handBox(deck) {

	//setting the text for seedNum
	seedNum.set_text("0");
	Hmenu.add(newGame);
	Hmenu.add(seedNum);
	Hmenu.add(quitGame);

	V.add(Hmenu);

	Vdialogbox.add(dialogBoxLabel);
	Hgame.add(Vdialogbox);
	

	//initializing the images. tableImages
	for (int i =0; i < 4; i ++){
		for (int k = 0; k < 13; k ++){
			// cout << i << " " << k << endl;
			Faces f = (Faces) k;
			Suits s = (Suits) i;
			Glib::RefPtr<Gdk::Pixbuf> *b = new Glib::RefPtr<Gdk::Pixbuf>( deck.getCardImage(f,s));

			cardImages[i][k] = (b);
			// cardImages[i][k]= new deck.getCardImage(f,s));
			tableImages[i][k]= new Gtk::Image(deck.getNullCardImage());
			// cout << "hre\n";
			// tableImages[i][k]->set((deck.getNullCardImage()));
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
			// cout << "end\n";

		}
	}
	Glib::RefPtr<Gdk::Pixbuf> b = deck.getCardImage(QUEEN,HEART);
	tableImages[0][1]->set(*cardImages[2][12]);
	// tableImages[0][3]->set(deck.getCardImage(QUEEN,CLUB));

	Vplay.add(Hclubs);
	Vplay.add(Hdiamonds);
	Vplay.add(Hhearts);
	Vplay.add(Hspades);


	//4 plays information fields. 
	for (int i = 0; i < 4; i ++){
		playerInfo[i] = new PlayerBox(i+1);
		HplayersBox.add(*playerInfo[i]);
	}
	Vplay.add(HplayersBox);
	// handBox = HandBox(Gtk::Image(deck.getNullCardImage()));
	//adding the Players starting hand.
	vector<Glib::RefPtr<Gdk::Pixbuf>*> blah;
	for (int i =0; i < 3; i++) {
		//tableImages[0][i] = &nothingImage;
		blah.push_back(cardImages[0][i]);
	}

	tableImages[0][1]->set(*cardImages[0][1]);
	handBox.setHand(blah);
	Vplay.add(handBox);

	Hgame.add(Vplay);
	V.add(Hgame);

	// (handBox.getButton(0)).signal_clicked().connect( sigc::mem_fun( *this, &View::onSeedNumButtonClicked ) );
	newGame.signal_clicked().connect( sigc::mem_fun( *this, &View::onSeedNumButtonClicked ) );
	quitGame.signal_clicked().connect( sigc::mem_fun( *this, &View::onQuitButtonClicked ) );
// 	add (frame);
	frame.add(V);
	add(frame);
	show_all();
}

View::~View(){
// 	for(int i = 0 ; i < 13; i++){
// 		delete card[i];
// 	}
}

void View::onButtonClicked(){
	// some_button.set_label("beat.");
}

void View::onSeedNumButtonClicked(){
	dialogBoxLabel.set_label(dialogBoxLabel.get_label() + "\n" + seedNum.get_text());
}

void View::onQuitButtonClicked(){
	dialogBoxLabel.set_label(dialogBoxLabel.get_label() + "\n" + "QUITTTT");
}

int main(int argc, char* argv[]){
	Gtk::Main kit (argc, argv);
	View window;
	Gtk::Main::run( window );

	//hand view!

	return 0;
 }

//SOME STUPID CODE!!!!
// 	cout<<"Set border width"<<endl;
// 	set_border_width(10);
// 	const Glib::RefPtr<Gdk::Pixbuf> noCard = deck.getNullCardImage();
// 	const Glib::RefPtr<Gdk::Pixbuf> some_Card = deck.getCardImage(QUEEN,HEART);

	
// 	frame.set_label("Beatiful: ");
// 	frame.set_label_align( Gtk::ALIGN_CENTER, Gtk::ALIGN_TOP );
 	
// 	//game.add(dialogBox);
// 	for (int i=0; i < 13; i++){
// 		card[i] = new Gtk::Image(deck.getCardImage(12,1));
// 		game.add(*card[i]);
// 	}
// 	for (int i=0; i < 13; i++){
// 		card[i] = new Gtk::Image(deck.getCardImage(QUEEN,HEART));
// 		diamonds.add(*card[i]);
// 	}
// 	for (int i=0; i < 13; i++){
// 		card[i] = new Gtk::Image(deck.getCardImage(QUEEN,HEART));
// 		clubs.add(*card[i]);
// 	}
// 	dialogBox.add(clubs);
// 	dialogBox.add (diamonds);

// //	Gtk::Image *none = new Gtk::Image ("cards_png/0_0.png");
// 	//diamonds.add(*none);
// 	//game.add(*none);

// 	some_button.signal_clicked().connect(sigc::mem_fun(*this, &View::onButtonClicked ));
	
// 	frame.add (game);
	
// 	game.add(dialogBox);
// 	game.add(some_button);
