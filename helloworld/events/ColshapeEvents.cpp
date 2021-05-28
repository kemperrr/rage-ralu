#include "RaluCore.hpp"

rage::IColshapeHandler *ColshapeEvents::GetColshapeHandler() {
	return this;
}

void ColshapeEvents::OnPlayerEnterColshape(rage::IPlayer *player, rage::IColshape *colshape) {
	ScriptArguments args;
	args.push(player);
	args.push(colshape);
	Events::GetInstance()->Call("playerEnterColshape", &args, EventHandler::rEventType::NATIVE_EVENT, 0, false);
}

void ColshapeEvents::OnPlayerExitColshape(rage::IPlayer *player, rage::IColshape *colshape) {
	ScriptArguments args;
	args.push(player);
	args.push(colshape);
	Events::GetInstance()->Call("playerExitColshape", &args, EventHandler::rEventType::NATIVE_EVENT, 0, false);
}
