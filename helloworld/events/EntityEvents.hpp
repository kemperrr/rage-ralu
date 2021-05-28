#pragma once
#include "rage.hpp"

class EntityEvents : public rage::IEventHandler, public rage::IEntityHandler {
public:
	rage::IEntityHandler *GetEntityHandler() override;

	void OnEntityCreated(rage::IEntity *entity);
	void OnEntityDestroyed(rage::IEntity *entity);
};