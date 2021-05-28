#pragma once
#include "rage.hpp"

class VehicleEvents : public rage::IEventHandler, public rage::IVehicleHandler {
public:
	rage::IVehicleHandler *GetVehicleHandler() override;

	void OnVehicleDeath(rage::IVehicle *vehicle, rage::hash_t hash, rage::IPlayer *killer);
};