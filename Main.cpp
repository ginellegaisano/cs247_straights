// #include "Game.h"
#include "View.h"
#include <iostream>
#include "Controller.h"
#include "Model.h"

using namespace std;


int main(int argc, char* argv[]){
	Gtk::Main kit (argc, argv);
	Model model;
	Controller controller(&model);
	View window(&controller, &model);
	Gtk::Main::run( window );

	//hand view!

	return 0;
 }