#pragma once
#include "rage.hpp"

class ColshapeEvents : public rage::IEventHandler, public rage::IColshapeHandler {
public:
	rage::IColshapeHandler *GetColshapeHandler() override;

	void OnPlayerEnterColshape(rage::IPlayer *player, rage::IColshape *colshape);
	void OnPlayerExitColshape(rage::IPlayer *player, rage::IColshape *colshape);
};