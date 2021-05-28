#include "NCCommand.hpp"

NCCommand::NCCommand() {

}

int NCCommand::addCommand(lua_State* state) {
	Resource* resource = ResourceManager::GetInstance()->getResourceByVM(state);

	if (!resource) {
		return 0;
	}

	luabridge::LuaRef commandName = luabridge::LuaRef::fromStack(state, 1);

	if (commandName.isString() && lua_isfunction(state, 2)) {
		int functionRef = luaL_ref(state, LUA_REGISTRYINDEX);
		Command* command = new Command(functionRef, resource->getVM());
		NCCommand* commandScript = new NCCommand();
		RaluCore::getInstance().getCommandManager()->addCommand(commandName, command);
		luabridge::push(state, commandScript);
		return 1;
	}

	return 0;

}

void NCCommand::Register(LuaVM* rVM) {
	getGlobalNamespace(rVM->GetVM())
	.beginClass<NCCommand>("NCCommand")
		
	.endClass()
	.beginNamespace("mp")
		.beginNamespace("commands")
			.addCFunction("add", &addCommand)
		.endNamespace()
	.endNamespace();
}