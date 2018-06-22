//
// Created by diego on 27/05/18.
//

#ifndef ROGUEEMBLEMGAME_OBSERVER_H
#define ROGUEEMBLEMGAME_OBSERVER_H

class Subject;

class Observer {
public:
	virtual ~Observer() = default;

	virtual void updateObserver(Subject* subject) = 0;
};
#endif //ROGUEEMBLEMGAME_OBSERVER_H
