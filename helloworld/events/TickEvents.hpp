#pragma once
#include "rage.hpp"

class TickEvents : public rage::IEventHandler, public rage::ITickHandler {
public:
	rage::ITickHandler *GetTickHandler() override;

	void Tick();
};