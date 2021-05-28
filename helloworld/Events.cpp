#include "Events.hpp"
#include <iostream>

Events* Events::r_eInstance = 0;

bool Events::Add(std::string strName, EventHandler* rEventHandler) {
	
	auto itEvent = r_Events.find(strName);
	if (itEvent == r_Events.end())
	{
		auto ret = r_Events.insert(std::pair<std::string, std::list<EventHandler*>>(strName, std::list<EventHandler*>()));
		itEvent = ret.first;

	} else {
		for (auto pEvent : itEvent->second)
		{
			if (rEventHandler->equals(pEvent))
				return false;
		}
	}

	itEvent->second.push_back(rEventHandler);
	return true;
}

bool Events::Remove(std::string strName, int refEventHandler) {
	auto itEvent = r_Events.find(strName);
	if (itEvent != r_Events.end())
	{
		for (EventHandler* pEvent : itEvent->second)
		{
			std::cout << pEvent->GetRef() << " " << refEventHandler << std::endl;
		}
	}
	return false;
}

bool Events::Remove(std::string strName, EventHandler* rEventHandler)
{
	auto itEvent = r_Events.find(strName);
	if (itEvent != r_Events.end())
	{
		/*for (EventHandler* pEvent : itEvent->second)
		{
			
			std::cout << lua_rawequal(rEventHandler->GetVM()->GetVM(), pEvent->GetRef(), rEventHandler->GetRef()) << std::endl;
		}*/
		for (auto pEvent = itEvent->second.begin(); pEvent != itEvent->second.end(); pEvent++)
		{
			if (rEventHandler->equals(*pEvent))
			{
				itEvent->second.erase(pEvent);
				if (itEvent->second.size() == 0)
				{
					
					r_Events.erase(itEvent);
					return true;
				}
			}
		}
	}
	return false;
}

bool Events::RemoveEventsCreatedByResource(Resource* pResource)
{
	LuaVM * resourceVM = pResource->getVM();
	std::string name;
	for (auto pEvent : r_Events)
	{
		name = pEvent.first;
		for (auto pEventHandler : pEvent.second)
		{
			if (pEventHandler->GetVM() == resourceVM)
			{
				Remove(name, pEventHandler);
			}
		}

	}
	return true;
}

bool Events::Call(std::string strName, ScriptArguments* arg, EventHandler::rEventType EventType, LuaVM* pVM, bool bIsTriggeredFromRemote) {
	auto itEvent = r_Events.find(strName);
	if (itEvent != r_Events.end())
	{
		for (auto pEvent : itEvent->second)
		{
			if (!pEvent->CanBeTriggeredFromRemote() && bIsTriggeredFromRemote)
				continue;
			
			if (EventType == EventHandler::rEventType::GLOBAL_EVENT
				&& pEvent->GetType() == EventHandler::GLOBAL_EVENT)
			{
				pEvent->Call(arg);
				
			}
			else if (EventType == EventHandler::rEventType::RESOURCE_EVENT
				&& pEvent->GetType() == EventHandler::RESOURCE_EVENT
				&& pEvent->GetVM() == pVM)
			{
				pEvent->Call(arg);
				
			}
			else if (EventType == EventHandler::rEventType::NATIVE_EVENT
				&& pEvent->GetType() == EventHandler::rEventType::RESOURCE_EVENT
				&& pVM == nullptr)
			{
				pEvent->Call(arg);
				
			}
			else if (EventType == EventHandler::rEventType::NATIVE_EVENT
				&& pEvent->GetType() == EventHandler::rEventType::RESOURCE_EVENT
				&& pEvent->GetVM() == pVM)
			{
				pEvent->Call(arg);
				
			}
		}
	}
	return false;
}

bool Events::IsEventRegistered(std::string strEventName)
{
	if (r_Events.find(strEventName) == r_Events.end()) {
		return false;
	}

	return true;
}

void Events::Clear()
{
	for (auto pEvent : r_Events)
	{
		for (auto event : pEvent.second)
		{
			SAFE_DELETE(event);
		}
		pEvent.second.clear();
	}
	r_Events.clear();
}