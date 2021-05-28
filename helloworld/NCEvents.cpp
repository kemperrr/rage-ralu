#include "NCEvents.hpp"


void NCEvents::Register(LuaVM* rVM) {
	getGlobalNamespace(rVM->GetVM())
		.beginClass<NCEvents>("NCEvents")
			.addCFunction("remove", &NCEvents::Remove)
			.addCFunction("call", &NCEvents::Call)
		.endClass()
		.beginNamespace("mp")
			.beginNamespace("events")
				.addCFunction("on", &addEvent)
				.addCFunction("add", &addEvent)
				.addCFunction("call", &callEvent)
				.addCFunction("callGlobal", &callGlobalEvent)
				.addCFunction("remove", &RemoveEvent)
				.addFunction("isRegistered", &IsRegistered)
			.endNamespace()
		.endNamespace();
}

NCEvents::NCEvents(EventHandler* handler, std::string nameEvent) {
	SetEventHandler(handler);
	SetEventName(nameEvent);
}

int NCEvents::Remove(lua_State* state) {
	Resource* resource = ResourceManager::GetInstance()->getResourceByVM(state);

	if (!resource) {
		return 0;
	}	

	luabridge::push(state, Events::GetInstance()->Remove(GetEventName(), GetEventHandler()));
	return 1;
}

int NCEvents::Call(lua_State* state) {
	Resource* resource = ResourceManager::GetInstance()->getResourceByVM(state);

	if (!resource) {
		return 0;
	}

	ScriptArguments args;

	for (int i = 2; i <= lua_gettop(state); i++) {
		luabridge::LuaRef arg = luabridge::LuaRef::fromStack(state, i);

		if (arg.isBoolean()) {
			args.push((bool)arg);
		}
		else if (arg.isString()) {
			args.push((const char*)arg);
		}
		else if (arg.isNumber()) {
			double n = arg;
			if (n == (int)n) {
				args.push((int)arg);
			}
			else {
				args.push((float)arg);
			}
		}
		else if (arg.isUserdata()) {

			std::string type = arg["type"];

			if (type == "player") {
				NCPlayer* player = arg;
				args.push(player->GetPlayer());
			}
			else if (type == "vehicle") {
				NCVehicle* vehicle = arg;
				args.push(vehicle->GetVehicle());
			}
			else if (type == "blip") {
				NCBlip* blip = arg;
				args.push(blip->GetBlip());
			}
			else if (type == "checkpoint") {
				NCCheckpoint* checkpoint = arg;
				args.push(checkpoint->GetCheckpoint());
			}
			else if (type == "marker") {
				NCMarker* marker = arg;
				args.push(marker->GetMarker());
			}
			else if (type == "colshape") {
				NCColshape* colshape = arg;
				args.push(colshape->GetColshape());
			}
			else if (type == "object") {
				NCObject* object = arg;
				args.push(object->GetObject());
			}
		}
		else if (arg.isTable()) {
			//ScriptArguments table;
			std::cout << arg.type() << " NCEvents " << std::endl;
			//ScriptArgument arggg = new ScriptArgument(&arg);
			args.push(arg);
		}
		else {
			args.push(NULL);
		}
	}

	Events::GetInstance()->Call(GetEventName(), &args, EventHandler::rEventType::RESOURCE_EVENT, resource->getVM(), false);
	return 0;
}

int NCEvents::RemoveEvent(lua_State* state) {
	Resource* resource = ResourceManager::GetInstance()->getResourceByVM(state);

	if (!resource) {
		return 0;
	}

	luabridge::LuaRef refHandler = luabridge::LuaRef::fromStack(state, 1);

	if (!refHandler.isUserdata()) {
		return 0;
	}

	NCEvents* handler = refHandler;

	luabridge::push(state, Events::GetInstance()->Remove(handler->GetEventName(), handler->GetEventHandler()));
	return 0;
}

int NCEvents::addEvent(lua_State* state) {
	Resource* resource = ResourceManager::GetInstance()->getResourceByVM(state);

	if (!resource) {
		return 0;
	}

	luabridge::LuaRef eventName = luabridge::LuaRef::fromStack(state, 1);

	if (eventName.isString() && lua_isfunction(state, 2)) {
		EventHandler* handler = new EventHandler(resource->getVM(), luaL_ref(state, LUA_REGISTRYINDEX), EventHandler::RESOURCE_EVENT, false);
		NCEvents* scriptEvent = new NCEvents(handler, eventName);
		handler->SetEventScript(scriptEvent);
		Events::GetInstance()->Add(eventName, handler);
		luabridge::push(state, scriptEvent);
		return 1;
	}

	return 0;
}
int NCEvents::callGlobalEvent(lua_State* state) {
	Resource* resource = ResourceManager::GetInstance()->getResourceByVM(state);

	if (!resource) {
		return 0;
	}

	luabridge::LuaRef eventName = luabridge::LuaRef::fromStack(state, 1);

	if (eventName.isString()) {
		ScriptArguments args;

		for (int i = 2; i <= lua_gettop(state); i++) {
			luabridge::LuaRef arg = luabridge::LuaRef::fromStack(state, i);

			if (arg.isBoolean()) {
				args.push((bool)arg);
			}
			else if (arg.isString()) {
				args.push((const char*)arg);
			}
			else if (arg.isNumber()) {
				double n = arg;
				if (n == (int)n) {
					args.push((int)arg);
				}
				else {
					args.push((float)arg);
				}
			}
			else if (arg.isUserdata()) {

				std::string type = arg["type"];

				if (type == "player") {
					NCPlayer* player = arg;
					args.push(player->GetPlayer());
				}
				else if (type == "vehicle") {
					NCVehicle* vehicle = arg;
					args.push(vehicle->GetVehicle());
				}
				else if (type == "blip") {
					NCBlip* blip = arg;
					args.push(blip->GetBlip());
				}
				else if (type == "checkpoint") {
					NCCheckpoint* checkpoint = arg;
					args.push(checkpoint->GetCheckpoint());
				}
				else if (type == "marker") {
					NCMarker* marker = arg;
					args.push(marker->GetMarker());
				}
				else if (type == "colshape") {
					NCColshape* colshape = arg;
					args.push(colshape->GetColshape());
				}
				else if (type == "object") {
					NCObject* object = arg;
					args.push(object->GetObject());
				}
			}
		}

		Events::GetInstance()->Call(eventName, &args, EventHandler::rEventType::NATIVE_EVENT, 0, false);
		return 0;
	}

	return 0;
}

int NCEvents::callEvent(lua_State* state) {
	Resource* resource = ResourceManager::GetInstance()->getResourceByVM(state);

	if (!resource) {
		return 0;
	}

	luabridge::LuaRef eventName = luabridge::LuaRef::fromStack(state, 1);

	if (eventName.isString()) {
		ScriptArguments args;

		for (int i = 2; i <= lua_gettop(state); i++) {
			luabridge::LuaRef arg = luabridge::LuaRef::fromStack(state, i);

			if (arg.isBoolean()) {
				args.push((bool)arg);
			} else if (arg.isString()) {
				args.push((const char*)arg);
			} else if (arg.isNumber()) {
				double n = arg;
				if (n == (int)n) {
					args.push((int)arg);
				} else {
					args.push((float)arg);
				}
			} else if (arg.isUserdata()) {

				std::string type = arg["type"];

				if (type == "player") {
					NCPlayer* player = arg;
					args.push(player->GetPlayer());
				}
				else if (type == "vehicle") {
					NCVehicle* vehicle = arg;
					args.push(vehicle->GetVehicle());
				}
				else if (type == "blip") {
					NCBlip* blip = arg;
					args.push(blip->GetBlip());
				}
				else if (type == "checkpoint") {
					NCCheckpoint* checkpoint = arg;
					args.push(checkpoint->GetCheckpoint());
				}
				else if (type == "marker") {
					NCMarker* marker = arg;
					args.push(marker->GetMarker());
				}
				else if (type == "colshape") {
					NCColshape* colshape = arg;
					args.push(colshape->GetColshape());
				}
				else if (type == "object") {
					NCObject* object = arg;
					args.push(object->GetObject());
				}	
			}
		}

		Events::GetInstance()->Call(eventName, &args, EventHandler::rEventType::RESOURCE_EVENT, resource->getVM(), false);
		return 0;
	}

	return 0;
}

bool NCEvents::IsRegistered(std::string eventName) {
	return Events::GetInstance()->IsEventRegistered(eventName);
}