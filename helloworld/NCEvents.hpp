#pragma once

#include "RaluCore.hpp"
#include "NCALL.hpp"

class NCEvents {
private:
	EventHandler* handlerEvent;
	std::string eventName;
public:
	NCEvents(EventHandler* handler, std::string nameEvent);
	int Remove(lua_State* state);
	int Call(lua_State* state);

	void SetEventHandler(EventHandler* handler) {
		handlerEvent = handler;
	}

	void SetEventName(std::string nameEvent) {
		eventName = nameEvent;
	}

	EventHandler* GetEventHandler() const {
		return handlerEvent;
	}

	std::string GetEventName() const {
		return eventName;
	}

	static void Register(LuaVM* rVM);
private:
	static int addEvent(lua_State* state);
	static int callEvent(lua_State* state);
	static int callGlobalEvent(lua_State* state);
	static int RemoveEvent(lua_State* state);
	static bool IsRegistered(std::string eventName);
};
