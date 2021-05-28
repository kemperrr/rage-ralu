#include "RaluCore.hpp"
#include <iostream>

rage::ITickHandler *TickEvents::GetTickHandler() {
	return this;
}

void TickEvents::Tick() {
	Events::GetInstance()->Call("update", NULL, EventHandler::rEventType::NATIVE_EVENT, 0, false);

	RaluCore::getInstance().getTimerManager()->Pulse();
}
