#include <set>
#include "Subject.h"
#include "Observer.h"
#include <iostream>

void Subject::subscribe(Observer* newObserve){
	observers_.insert(newObserve);
}

void Subject::unsubscribe(Observer* oldObserve){
	observers_.erase(oldObserve);
}

void Subject::notify(){
	std::cout << "notifying...\n";
	Observers::iterator i;
	for (i = observers_.begin(); i != observers_.end(); ++i) (*i)->update();
}