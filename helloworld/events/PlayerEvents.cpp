#include "RaluCore.hpp"
#include <iostream>
#include <locale> 
#include <codecvt> 
#include "LuaBridge.h"
#include "NCPlayer.hpp"
#include <iterator>

using namespace luabridge;

rage::IPlayerHandler *PlayerEvents::GetPlayerHandler() {
	return this;
}


void PlayerEvents::OnPlayerJoin(rage::IPlayer *player) {

	NCPlayer* scriptPlayer = new NCPlayer(player);
	player->External(scriptPlayer);

	ScriptArguments argsForCreated;
	argsForCreated.push(player);
	Events::GetInstance()->Call("entityCreated", &argsForCreated, EventHandler::rEventType::NATIVE_EVENT, 0, false);


	ScriptArguments args;
	args.push(player);

	if (!Events::GetInstance()->IsEventRegistered("playerJoin"))
	{
		rage::vector3 vec = { 0, 0, 72 };
		player->SetHealth(100);
		player->Spawn(vec, 0);
		player->SetModel(Utility::joaat("MP_F_Freemode_01"));
	}
	
	Events::GetInstance()->Call("playerJoin", &args, EventHandler::rEventType::NATIVE_EVENT, 0, false);
}

void PlayerEvents::OnPlayerCommand(rage::IPlayer *player, const std::u16string &command) {
	ScriptArguments args;
	args.push(player);

	std::wstring_convert<std::codecvt_utf8_utf16<int16_t>, int16_t> convert;
	auto p = reinterpret_cast<const int16_t *>(command.data());
	std::string convertedString = convert.to_bytes(p, p + command.size());

	std::istringstream buf(convertedString);
	std::istream_iterator<std::string> beg(buf), end;

	std::vector<std::string> vecSplit(beg, end);

	if (vecSplit.size() == 0) {
		return;
	}

	RaluCore::getInstance().getCommandManager()->manageCommand(vecSplit[0], player, vecSplit);

	args.push(convertedString);
	Events::GetInstance()->Call("playerCommand", &args, EventHandler::rEventType::NATIVE_EVENT, 0, false);
}

void PlayerEvents::OnPlayerQuit(rage::IPlayer *player, rage::exit_t exitType, const char *reason) {
	ScriptArguments args;
	args.push(player);
	Events::GetInstance()->Call("playerQuit", &args, EventHandler::rEventType::NATIVE_EVENT, 0, false);
}

void PlayerEvents::OnPlayerSpawn(rage::IPlayer *player) {
	ScriptArguments args;
	args.push(player);

	Events::GetInstance()->Call("playerSpawn", &args, EventHandler::rEventType::NATIVE_EVENT, 0, false);
}

void PlayerEvents::OnPlayerChat(rage::IPlayer *player, const std::u16string &text) {
	ScriptArguments args;
	args.push(player);

	std::wstring_convert<std::codecvt_utf8_utf16<int16_t>, int16_t> convert;
	auto p = reinterpret_cast<const int16_t *>(text.data());
	std::string convertedString = convert.to_bytes(p, p + text.size());

	args.push(convertedString);

	Events::GetInstance()->Call("playerChat", &args, EventHandler::rEventType::NATIVE_EVENT, 0, false);
}

void PlayerEvents::OnPlayerEnterVehicle(rage::IPlayer *player, rage::IVehicle *vehicle, uint8_t seatId) {
	ScriptArguments args;
	args.push(player);
	args.push(vehicle);
	args.push(seatId);
	Events::GetInstance()->Call("playerEnterVehicle", &args, EventHandler::rEventType::NATIVE_EVENT, 0, false);
}

void PlayerEvents::OnPlayerEnteredVehicle(rage::IPlayer *player, rage::IVehicle *vehicle, uint8_t seatId) {
	ScriptArguments args;
	args.push(player);
	args.push(vehicle);
	args.push(seatId);
	Events::GetInstance()->Call("playerEnteredVehicle", &args, EventHandler::rEventType::NATIVE_EVENT, 0, false);
}

void PlayerEvents::OnPlayerExitVehicle(rage::IPlayer *player, rage::IVehicle *vehicle) {
	ScriptArguments args;
	args.push(player);
	args.push(vehicle);
	Events::GetInstance()->Call("playerExitVehicle", &args, EventHandler::rEventType::NATIVE_EVENT, 0, false);
}

void PlayerEvents::OnPlayerLeftVehicle(rage::IPlayer *player, rage::IVehicle *vehicle) {
	ScriptArguments args;
	args.push(player);
	args.push(vehicle);
	Events::GetInstance()->Call("playerLeftVehicle", &args, EventHandler::rEventType::NATIVE_EVENT, 0, false);
}

void PlayerEvents::OnPlayerDeath(rage::IPlayer *player, rage::hash_t reason, rage::IPlayer *killer) {
	ScriptArguments args;
	args.push(player);
	args.push((int)reason);

	if (killer) {
		args.push(killer);
	} else {
		args.push(NULL);
	}
	Events::GetInstance()->Call("playerDeath", &args, EventHandler::rEventType::NATIVE_EVENT, 0, false);
}

void PlayerEvents::OnPlayerRemoteEvent(rage::IPlayer *player, const std::string &eventName, const rage::args_t &argsEvent) {
	ScriptArguments args;
	args.push(player);

	for (int i = 0; i < argsEvent.Length(); i++)
	{
		if (argsEvent[i].IsBoolean()) {
			args.push(argsEvent[i].Boolean());
		} else if (argsEvent[i].IsFloat()) {
			args.push(argsEvent[i].Float());
		} else if (argsEvent[i].IsInt()) {
			args.push(argsEvent[i].Int());
		} else if (argsEvent[i].IsString()) {
			args.push(argsEvent[i].String());
		} else if (argsEvent[i].IsNull()) {
			args.push(NULL);
		} else if (argsEvent[i].IsEntity()) {
			args.push(argsEvent[i].Entity());
		}
	}
	Events::GetInstance()->Call(eventName, &args, EventHandler::rEventType::NATIVE_EVENT, 0, false);
}