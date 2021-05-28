#include "Command.hpp"
#include "NCPlayer.hpp"
#include <algorithm>
#include <cctype>

Command::Command(int refFunction, LuaVM* r_VM) {
	functionRef = refFunction;
	rVM = r_VM;
}

bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

void Command::call(rage::IPlayer *player, std::vector<std::string> args) {

	args.erase(args.begin());

	lua_rawgeti(rVM->GetVM(), LUA_REGISTRYINDEX, functionRef);
	NCPlayer* scriptPlayer = player->External<NCPlayer>();
	luabridge::push(rVM->GetVM(), scriptPlayer);

	luabridge::LuaRef table = luabridge::LuaRef::newTable(rVM->GetVM());
	table["argsCount"] = (int)args.size();
	luabridge::push(rVM->GetVM(), table);

	for (auto arg : args) {
		if (is_number(arg)) {
			luabridge::push(rVM->GetVM(), std::stoi(arg));
		}
		else if (arg == "true") {
			luabridge::push(rVM->GetVM(), true);
		}
		else if (arg == "false") {
			luabridge::push(rVM->GetVM(), false);
		} else {
			luabridge::push(rVM->GetVM(), arg);
		}
	}

	lua_pcall(rVM->GetVM(), (int)args.size() + 2, LUA_MULTRET, NULL);
	lua_settop(rVM->GetVM(), 0);
}