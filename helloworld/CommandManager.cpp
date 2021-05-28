#include "CommandManager.hpp"

void CommandManager::addCommand(std::string commandName, Command* command) {
	commands.insert(std::pair<std::string, Command*>(commandName, command));
}

void CommandManager::manageCommand(std::string commandName, rage::IPlayer *player, std::vector<std::string> args) {
	auto search = commands.find(commandName);
	if (search != commands.end())
	{
		search->second->call(player, args);
	}
}