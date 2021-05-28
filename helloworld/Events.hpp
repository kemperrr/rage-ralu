#pragma once
#include "RaluCore.hpp"
#include "EventHandler.hpp"
#include <map>
#include "ScriptArgument.hpp"
#include "ScriptArguments.hpp"

class Events {
private:
	static Events* r_eInstance;

	std::map<std::string, std::list<EventHandler*>> r_Events;
public:
	Events() {
		r_eInstance = this;
	}
	~Events();

	static Events* GetInstance() { return r_eInstance; }

	bool Add(std::string strName, EventHandler* rEventHandler);

	bool Remove(std::string strName, int refEventHandler);
	bool Remove(std::string strName, EventHandler* rEventHandler);
	bool RemoveEventsCreatedByResource(Resource* pResource);

	bool Call(std::string strName, ScriptArguments* arg, EventHandler::rEventType EventType, LuaVM* pVM, bool bIsTriggeredFromRemote);

	bool IsEventRegistered(std::string eventName);

	void Clear();
};