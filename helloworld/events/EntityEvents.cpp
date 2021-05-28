#include "RaluCore.hpp"
#include "Events.hpp"
#include "Utility.hpp"
#include "LuaBridge.h"
#include "NCALL.hpp"
#include <iostream>
#include <dos.h>

using namespace luabridge;

rage::IEntityHandler *EntityEvents::GetEntityHandler() {
	return this;
}

void EntityEvents::OnEntityCreated(rage::IEntity *entity) {

	if (entity->GetType() == rage::entity_t::Player) {
		return;
	} else if (entity->GetType() == rage::entity_t::Checkpoint) {
		NCCheckpoint* scriptCheckpoint = new NCCheckpoint(entity);
		entity->External(scriptCheckpoint);
	} else if (entity->GetType() == rage::entity_t::Vehicle) {
		NCVehicle* scriptVehicle = new NCVehicle(entity);
		entity->External(scriptVehicle);
	} else if (entity->GetType() == rage::entity_t::Blip) {
		NCBlip* scriptBlip = new NCBlip(entity);
		entity->External(scriptBlip);
	} else if (entity->GetType() == rage::entity_t::Marker) {
		NCMarker* scriptMarker = new NCMarker(entity);
		entity->External(scriptMarker);
	} else if (entity->GetType() == rage::entity_t::Colshape) {
		NCColshape* scriptColshape = new NCColshape(entity);
		entity->External(scriptColshape);
	} else if (entity->GetType() == rage::entity_t::Object) {
		NCObject* scriptObject = new NCObject(entity);
		entity->External(scriptObject);
	}

	ScriptArguments args;
	args.push(entity);
	Events::GetInstance()->Call("entityCreated", &args, EventHandler::rEventType::NATIVE_EVENT, 0, false);
}
	

void EntityEvents::OnEntityDestroyed(rage::IEntity *entity) {

	ScriptArguments args;
	args.push(entity);
	Events::GetInstance()->Call("entityDestroyed", &args, EventHandler::rEventType::NATIVE_EVENT, 0, false);

	if (entity->GetType() == rage::entity_t::Player) {
		NCPlayer* scriptPlayer = entity->External<NCPlayer>();
		scriptPlayer->ClearEntity();
	}

}

