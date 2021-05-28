#include "Timer.hpp"
#include <ctime>
#include <iostream>
#include <chrono>
#include <vector>

Timer::Timer(int interval, int func, LuaVM* VM, bool is_Timeout)
{
	r_Interval = interval;
	r_LastPulse = is_Timeout ? std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() : 0;
	refFunc = func;
	currentTick = 0;
	rVM = VM;
	isPaused = false;
	isRemove = false;

	isTimeout = is_Timeout;
}

bool Timer::Pulse() {

	if (isRemove) {
		return false;
	}

	if (isTimeout && currentTick >= 1) {
		return false;
	}

	if (isPaused) {
		return true;
	}

	long long timeNow = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
	if (timeNow >= r_LastPulse + r_Interval) {

		lua_rawgeti(rVM->GetVM(), LUA_REGISTRYINDEX, refFunc);
		luabridge::push(rVM->GetVM(), currentTick);
		lua_pcall(rVM->GetVM(), 1, LUA_MULTRET, NULL);
		lua_settop(rVM->GetVM(), 0);

		currentTick++;
		r_LastPulse = timeNow;
	}

	return true;
}