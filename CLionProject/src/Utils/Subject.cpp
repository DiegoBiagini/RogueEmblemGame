//
// Created by diego on 27/05/18.
//

#include "Subject.h"

Subject::~Subject() {

}

void Subject::attach(Observer * obs) {
	observers.push_back(obs);
}

void Subject::detach(Observer * obs) {
	observers.erase(std::find(observers.begin(), observers.end(), obs));
}

void Subject::notify() {
	for (auto el : observers)
		el->updateObserver(this);
}
