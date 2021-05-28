#include "NCTimer.hpp"

NCTimer::NCTimer(Timer* timer) {
	SetTimerHandler(timer);
}

int NCTimer::Pause(lua_State* state) {
	GetTimerHandler()->Pause();
	return 0;
}

int NCTimer::Start(lua_State* state) {
	GetTimerHandler()->Resume();
	return 0;
}

int NCTimer::Remove(lua_State* state) {
	GetTimerHandler()->Remove();
	return 0;
}

int NCTimer::CreateInterval(lua_State* state) {

	Resource* resource = ResourceManager::GetInstance()->getResourceByVM(state);

	if (!resource) {
		return 0;
	}

	if (lua_isfunction(state, 1) && lua_isnumber(state, 2)) {
		lua_pushvalue(state, 1);
		int refFunction = luaL_ref(state, LUA_REGISTRYINDEX);
		LuaRef refInterval = LuaRef::fromStack(state, 2);
		Timer* timer = new Timer(refInterval, refFunction, resource->getVM(), false);
		RaluCore::getInstance().getTimerManager()->push_back(timer);
		NCTimer* scriptTimer = new NCTimer(timer);
		luabridge::push(state, scriptTimer);

		refInterval = NULL;
		refFunction = NULL;

		return 1;
	}
	return 0;
}

int NCTimer::CreateTimeout(lua_State* state) {

	Resource* resource = ResourceManager::GetInstance()->getResourceByVM(state);

	if (!resource) {
		return 0;
	}

	if (lua_isfunction(state, 1) && lua_isnumber(state, 2)) {
		lua_pushvalue(state, 1);
		int refFunction = luaL_ref(state, LUA_REGISTRYINDEX);
		LuaRef refInterval = LuaRef::fromStack(state, 2);
		Timer* timer = new Timer(refInterval, refFunction, resource->getVM(), true);
		RaluCore::getInstance().getTimerManager()->push_back(timer);
		NCTimer* scriptTimer = new NCTimer(timer);
		luabridge::push(state, scriptTimer);
		
		refInterval = NULL;
		refFunction = NULL;

		return 1;
	}
	return 0;
}

int NCTimer::ClearTimer(lua_State* state) {
	luabridge::LuaRef refTimer = luabridge::LuaRef::fromStack(state, 1);

	if (refTimer.isUserdata()) {
		NCTimer* timer = refTimer;

		timer->GetTimerHandler()->Remove();

		delete timer;
	}

	return 0;
}

void NCTimer::Register(LuaVM* rVM) {
	getGlobalNamespace(rVM->GetVM())
		.beginClass<NCTimer>("NCTimer")
			.addCFunction("pause", &NCTimer::Pause)
			.addCFunction("resume", &NCTimer::Start)
			.addCFunction("remove", &NCTimer::Remove)
		.endClass()
		.addCFunction("setInterval", &CreateInterval)
		.addCFunction("setTimeout", &CreateTimeout)
		.addCFunction("clearTimer", &ClearTimer);
}