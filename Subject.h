#ifndef SUBJECT_H
#define SUBJECT_H

class Subject {
	public:
		subscribe (Observer*);
		unsubscribe(Observer*);
	protected:
		notify();
};

#endif