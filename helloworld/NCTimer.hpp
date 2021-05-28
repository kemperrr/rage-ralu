#pragma once

#include "RaluCore.hpp"
#include "NCALL.hpp"

class NCTimer {
private:
	Timer* timerHandler;
public:

	NCTimer(Timer* timer);

	int Pause(lua_State* state);
	int Start(lua_State* state);
	int Remove(lua_State* state);

	Timer* GetTimerHandler() {
		return timerHandler;
	}

	void SetTimerHandler(Timer* timer) {
		timerHandler = timer;
	}

	static void Register(LuaVM* rVM);
private:
	static int CreateInterval(lua_State* state);
	static int CreateTimeout(lua_State* state);
	static int ClearTimer(lua_State* state);
};