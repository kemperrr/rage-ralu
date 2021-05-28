#pragma once

#include "rage.hpp"

class CheckpointEvents : public rage::IEventHandler, public rage::ICheckpointHandler {
public:
	rage::ICheckpointHandler *GetCheckpointHandler() override;

	void OnPlayerEnterCheckpoint(rage::IPlayer *player, rage::ICheckpoint *checkpoint);
	void OnPlayerExitCheckpoint(rage::IPlayer *player, rage::ICheckpoint *checkpoint);
};