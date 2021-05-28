#pragma once

#include "rage.hpp"
#include <unordered_map>
#include <functional>
#include "Command.hpp"
#include <vector>

class Command;

class CommandManager {
private:
	std::unordered_map<std::string, Command*> commands;
public:
	CommandManager() {

	}

	void manageCommand(std::string commandName, rage::IPlayer *player, std::vector<std::string> args);
	void addCommand(std::string commandName, Command* command);

};