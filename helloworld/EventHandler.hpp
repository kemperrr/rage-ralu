#pragma once
#include "LuaVM.hpp"
#include <iostream>
#include "LuaBridge.h"
#include "lua.hpp"
#include "ScriptArgument.hpp"
#include "ScriptArguments.hpp"

class NCEvents;

using namespace luabridge;
class EventHandler {
public:
	enum rEventType
	{
		RESOURCE_EVENT,
		GLOBAL_EVENT,
		REMOTE_EVENT,
		NATIVE_EVENT,
	};
private:
	LuaVM* r_pVM;
	rEventType r_EventType;
	int r_iRef;
	bool r_bCanBeTriggeredFromRemote;

	NCEvents* eventScript;
public:
	EventHandler(LuaVM * rVM, int ref, rEventType EventType = RESOURCE_EVENT, bool bCanBeTriggeredFromRemote = false) {
		r_pVM = rVM;
		r_EventType = EventType;
		r_iRef = ref;
		r_bCanBeTriggeredFromRemote = bCanBeTriggeredFromRemote;
	}

	~EventHandler() {

	}

	void SetEventScript(NCEvents* scriptEvent) {
		eventScript = scriptEvent;
	}

	virtual LuaVM* GetVM() { return r_pVM; }
	int GetRef() { return r_iRef; }
	rEventType GetType() { return r_EventType; }
	NCEvents* GetEventScript() { return eventScript; }

	void Call(ScriptArguments* args)
	{
		lua_rawgeti(r_pVM->GetVM(), LUA_REGISTRYINDEX, r_iRef);
		if (args)
		{
			for (auto it : args->m_Arguments)
			{
				it->Push(r_pVM);
			}
			lua_pcall(r_pVM->GetVM(), (int)args->m_Arguments.size(), LUA_MULTRET, NULL);
		} else {
			lua_pcall(r_pVM->GetVM(), 0, LUA_MULTRET, NULL);
		}
		lua_settop(r_pVM->GetVM(), 0);
	}

	bool equals(EventHandler* other)
	{
		//std::cout << (other->GetVM() == GetVM()) << (other->GetType() == GetType()) << (other->GetRef() == GetRef()) << std::endl;
		return (other->GetVM()
			&& other->GetVM() == GetVM()
			&& other->GetType() == GetType()
			&& other->GetRef() == GetRef());
	}

	bool CanBeTriggeredFromRemote()
	{
		return r_bCanBeTriggeredFromRemote;
	}
};