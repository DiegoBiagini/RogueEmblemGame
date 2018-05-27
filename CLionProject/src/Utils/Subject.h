//
// Created by diego on 27/05/18.
//

#ifndef ROGUEEMBLEMGAME_SUBJECT_H
#define ROGUEEMBLEMGAME_SUBJECT_H

#include <vector>
#include <algorithm>
#include "Observer.h"


class Subject {
public:
	virtual ~Subject();

	virtual void attach(Observer* obs);
	virtual void detach(Observer* obs);
	virtual void notify();

private:
	std::vector<Observer*> observers;

};
#endif //ROGUEEMBLEMGAME_SUBJECT_H
