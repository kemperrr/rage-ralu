#pragma once
#include <lua.hpp>
#include "PlayerEvents.hpp"
#include "VehicleEvents.hpp"
#include "EntityEvents.hpp"
#include "ColshapeEvents.hpp"
#include "TickEvents.hpp"
#include "CheckpointEvents.h"
#include "ResourceManager.hpp"
#include "Events.hpp"
#include "rage.hpp"
#include "ScriptArgument.hpp"
#include "ScriptArguments.hpp"
#include "Utility.hpp"
#include "TimerManager.hpp"
#include "CommandManager.hpp"

#define RESOURCE_DIRECTORY "/resources"

#define SAFE_DELETE(a) if( (a) != NULL ) delete (a); (a) = NULL;

class CommandManager;

class RaluCore {
public:
	static RaluCore& getInstance() {
		static RaluCore rageRaluCore;
		return rageRaluCore;
	}

	rage::IMultiplayer *getMultiPlayer() {
		return mp;
	}

	ResourceManager* getResourceManager() {
		return instanceResourceManager;
	}

	TimerManager* getTimerManager() {
		return instanceTimerManager;
	}

	CommandManager* getCommandManager() {
		return instanceCommandManager;
	}

	bool initialize(rage::IMultiplayer *mp);

private:
	ResourceManager* instanceResourceManager;
	TimerManager* instanceTimerManager;
	CommandManager* instanceCommandManager;
	bool initializeEventHandlers();
	rage::IMultiplayer *mp;
};
