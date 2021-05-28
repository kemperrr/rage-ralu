#include "RaluCore.hpp"

rage::ICheckpointHandler *CheckpointEvents::GetCheckpointHandler() {
	return this;
}

void CheckpointEvents::OnPlayerEnterCheckpoint(rage::IPlayer *player, rage::ICheckpoint *checkpoint) {
	ScriptArguments args;

	args.push(player);
	args.push(checkpoint);
	Events::GetInstance()->Call("playerEnterCheckpoint", &args, EventHandler::rEventType::NATIVE_EVENT, 0, false);
}

void CheckpointEvents::OnPlayerExitCheckpoint(rage::IPlayer *player, rage::ICheckpoint *checkpoint) {
	ScriptArguments args;
	args.push(player);
	args.push(checkpoint);
	Events::GetInstance()->Call("playerExitCheckpoint", &args, EventHandler::rEventType::NATIVE_EVENT, 0, false);
}
