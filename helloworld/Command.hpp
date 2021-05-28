#pragma once
#include "RaluCore.hpp"
#include <string>
#include <vector>

class Command {

private:
	LuaVM* rVM;
	int functionRef;

public:
	Command(int functionRef, LuaVM* r_VM);

	void call(rage::IPlayer *player, std::vector<std::string> args);

};