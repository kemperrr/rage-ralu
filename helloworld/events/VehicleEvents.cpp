#include "RaluCore.hpp"

rage::IVehicleHandler *VehicleEvents::GetVehicleHandler() {
	return this;
}

void VehicleEvents::OnVehicleDeath(rage::IVehicle *vehicle, rage::hash_t hash, rage::IPlayer *killer) {
	ScriptArguments args;
	args.push(vehicle);
	args.push((int)hash);
	if (killer) {
		args.push(killer);
	} else {
		args.push(NULL);
	}
	Events::GetInstance()->Call("vehicleDeath", &args, EventHandler::rEventType::NATIVE_EVENT, 0, false);
}