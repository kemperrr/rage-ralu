#pragma once

#include "Timer.hpp"
#include <list>

class Timer;

class TimerManager : public std::list<Timer *> {
public:
	TimerManager();
	~TimerManager();

	void Pulse();

};