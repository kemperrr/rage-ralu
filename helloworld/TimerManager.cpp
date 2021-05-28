
#include "TimerManager.hpp"
#include <iostream>

TimerManager::TimerManager() {

}

TimerManager::~TimerManager() {

}

void TimerManager::Pulse() {
	for (iterator it = begin(); it != end();) {
		if (!(*it)->Pulse())
		{
			it = erase(it);
		} else {
			++it;
		}
	}
}