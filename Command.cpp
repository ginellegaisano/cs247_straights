#include "Command.h"
#include <cassert>
#include <sstream>
using namespace std;

istream &operator>>(istream &in, Command &c){
	c.type = BAD_COMMAND;
	
	string cmd;
	in >> cmd;
	
	if (cmd == "play") {
		c.type = PLAY;
		in >> c.card;
	} else if (cmd == "discard") {
		c.type = DISCARD;
		in >> c.card;
	} else if (cmd == "deck") {
		c.type = DECK;
	} else if (cmd == "quit") {
		c.type = QUIT;
	} else if (cmd == "ragequit") {
		c.type = RAGEQUIT;
	}
	
	assert(!in.fail() && c.type != BAD_COMMAND);
	
	return in;
}

ostream &operator<<(ostream &sout, Command &c){
	
	if (c.type == PLAY) {
		sout <<"plays";
	} else if (c.type == DISCARD) {
		sout <<"discards";
	} else if (c.type == DECK) {
		sout <<"deck";
	} else if (c.type == QUIT) {
		sout <<"quit";
	} else if (c.type == RAGEQUIT) {
		sout <<"ragequit";
	}
	else {
		sout <<"";
	}

	return sout;
}