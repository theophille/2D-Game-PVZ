#pragma once

#include "observer.h"

class Subject {
public: 
	virtual void subscribe(Observer* obs, int subscription) = 0;
	virtual void unsubscribe(Observer* obs, int subscription) = 0;
	virtual void notifyObservers(int subscription) = 0;
};