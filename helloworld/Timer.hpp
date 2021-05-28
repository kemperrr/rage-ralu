#pragma once
#include "LuaVM.hpp"
#include "LuaBridge.h"

class LuaVM;

class Timer {
private:
	unsigned int r_Interval;
	long long r_LastPulse;
	int refFunc;
	int currentTick;
	LuaVM* rVM;

	bool isPaused;
	bool isRemove;

	bool isTimeout;

public:
	Timer(int interval, int ref, LuaVM* VM, bool isTimeout);

	void Pause() { isPaused = true; }
	void Resume() { isPaused = false; }

	void Remove() { isRemove = true; }

	~Timer();
	bool Pulse();
};