#ifndef VIEW_H
#define VIEW_H

#include <gtkmm.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "DeckGUI.h"
#include "stdio.h"
#include "Controller.h"
#include "Model.h"
#include "Observer.h"


using namespace std;

class View : public Gtk::Window, public Observer{
	public:
		View(Controller*, Model*);
		virtual ~View();
		// void update();
	private:
		Controller *controller_;
		Model *model_;
		//signal handlers?
		virtual void onButtonClicked();
		virtual void onSeedNumButtonClicked();
		virtual void onQuitButtonClicked();
		virtual void onRageQuitButtonClicked(int);
		virtual void onCardButtonClicked(int);
		virtual void onDialogButtonClicked();
		virtual void update();
		virtual void setHand(vector<pair<int, int> >);
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

#endif