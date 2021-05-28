#include "NCMarker.hpp"

NCMarker::NCMarker(rage::IEntity* entryEntity) {
	SetEntity(entryEntity);
}

void NCMarker::Destroy() {
	GetMarker()->Destroy();
	ClearEntity();
}

int NCMarker::GetColour(lua_State* state) {
	rage::rgba_t colour = GetMarker()->GetColour();
	luabridge::push(state, colour.rgba[0]);
	luabridge::push(state, colour.rgba[1]);
	luabridge::push(state, colour.rgba[2]);
	luabridge::push(state, colour.rgba[3]);
	return 4;
}

void NCMarker::SetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	GetMarker()->SetColour(r, g, b, a);
}

NCVector3* NCMarker::GetDirection() const {
	rage::vector3 vec = GetMarker()->GetDirection();
	return new NCVector3(vec.x, vec.y, vec.z);
}

void NCMarker::SetDirection(NCVector3* dir) {
	rage::vector3 vec = { dir->coord[0], dir->coord[1], dir->coord[2] };
	GetMarker()->SetDirection(vec);
}

float NCMarker::GetScale() const {
	return GetMarker()->GetScale();
}

void NCMarker::SetScale(float scale) {
	GetMarker()->SetScale(scale);
}

bool NCMarker::IsVisible() const {
	return GetMarker()->IsVisible();
}

void NCMarker::SetVisible(bool toggle) {
	GetMarker()->SetVisible(toggle);
}

int NCMarker::ShowFor(lua_State* state) {
	std::vector<rage::IPlayer*> players;

	for (int i = 2; i <= lua_gettop(state); i++) {
		NCPlayer* ref = Userdata::get<NCPlayer>(state, i, false);
		if (ref->GetType() == "player" && std::find(players.begin(), players.end(), ref->GetPlayer()) == players.end()) {
			players.push_back(ref->GetPlayer());
		}
	}

	GetMarker()->ShowFor(players);
	return 0;
}

int NCMarker::HideFor(lua_State* state) {
	std::vector<rage::IPlayer*> players;

	for (int i = 2; i <= lua_gettop(state); i++) {
		NCPlayer* ref = Userdata::get<NCPlayer>(state, i, false);
		if (ref->GetType() == "player" && std::find(players.begin(), players.end(), ref->GetPlayer()) == players.end()) {
			players.push_back(ref->GetPlayer());
		}
	}

	GetMarker()->HideFor(players);
	return 0;
}

bool NCMarker::operator==(NCMarker* checkpoint) const {
	return checkpoint->GetEntity() == GetEntity();
}

int NCMarker::CreateMarker(lua_State* state) {
	uint32_t model = 0;
	rage::vector3 vec;
	rage::vector3 rot = { 0,0,0 };
	rage::vector3 dir = { 0,0,0 };
	float scale = 1;

	rage::rgba_t color;
	color.rgba[0] = 255;
	color.rgba[1] = 255;
	color.rgba[2] = 255;
	color.rgba[3] = 255;

	bool visible = true;
	uint32_t dimension = 0;

	if (lua_isnumber(state, 1)) {
		model = (uint32_t)lua_tonumber(state, 1);
	} else {
		return 0;
	}

	if (lua_isuserdata(state, 2)) {
		NCVector3* vector = Userdata::get<NCVector3>(state, 2, false);

		vec = { vector->coord[0] , vector->coord[1] , vector->coord[2] };

	} else if (lua_istable(state, 2)) {
		LuaRef ref = LuaRef::fromStack(state, 2);

		float x = ref["x"];
		float y = ref["y"];
		float z = ref["z"];

		vec = { x , y , z };
	} else {
		return 0;
	}

	LuaRef settings = LuaRef::fromStack(state, 3);

	if (settings.isTable()) {
		if (settings["scale"].isNumber()) {
			scale = settings["scale"];
		}

		if (settings["direction"].isUserdata()) {
			NCVector3* vector = settings["direction"];
			dir = { vector->coord[0] , vector->coord[1] , vector->coord[2] };
		}

		if (settings["rotation"].isUserdata()) {
			NCVector3* vector = settings["rotation"];
			rot = { vector->coord[0] , vector->coord[1] , vector->coord[2] };
		}

		if (settings["r"].isNumber()) {
			color.rgba[0] = settings["r"];
		}

		if (settings["g"].isNumber()) {
			color.rgba[1] = settings["g"];
		}

		if (settings["b"].isNumber()) {
			color.rgba[2] = settings["b"];
		}

		if (settings["a"].isNumber()) {
			color.rgba[3] = settings["a"];
		}

		if (settings["dimension"].isNumber()) {
			dimension = settings["dimension"];
		}

		if (settings["visible"].isBoolean()) {
			visible = settings["visible"];
		}
	}

	rage::IMarker* marker = RaluCore::getInstance().getMultiPlayer()->GetMarkerPool().New(model, vec, rot, dir, scale, color, visible, dimension);

	NCMarker* scriptMarker = marker->External<NCMarker>();
	push(state, scriptMarker);
	return 1;
}

int NCMarker::GetAtMarker(lua_State* state) {
	LuaRef ref = LuaRef::fromStack(state, 1);

	if (!ref.isNumber()) {
		return 0;
	}

	rage::IMarker* marker = RaluCore::getInstance().getMultiPlayer()->GetMarkerPool().GetAt(ref);

	if (!marker) {
		return 0;
	}

	NCMarker* scriptMarker = marker->External<NCMarker>();

	push(state, scriptMarker);
	return 1;
}

bool NCMarker::Exists(NCMarker* marker) {
	return marker->entity ? true : false;
}

int NCMarker::ForEach(lua_State* state) {
	LuaRef func = LuaRef::fromStack(state, 1);
	int size = 1;
	if (func.isFunction()) {
		for (rage::IMarker* marker : RaluCore::getInstance().getMultiPlayer()->GetMarkerPool()) {
			func(marker->External<NCMarker>(), size);
			size++;
		}
	}
	return 0;

}

int NCMarker::ToArray(lua_State* state) {
	LuaRef table = LuaRef::newTable(state);

	for (rage::IMarker* marker : RaluCore::getInstance().getMultiPlayer()->GetMarkerPool()) {
		table.append(marker->External<NCMarker>());
	}

	push(state, table);
	return 1;
}

int NCMarker::GetSize() {
	int size = 0;
	for (rage::IMarker* marker : RaluCore::getInstance().getMultiPlayer()->GetMarkerPool()) { size++; }
	return size;
}

void NCMarker::Register(LuaVM* rVM) {
	getGlobalNamespace(rVM->GetVM())
	.beginClass<NCMarker>("NCMarker")
		.addFunction("__eq", &NCMarker::operator==)
		.addProperty("id", &NCMarker::GetId)
		.addProperty("type", &NCMarker::GetType)
		.addFunction("destroy", &NCMarker::Destroy)
		.addProperty("dimension", &NCMarker::GetDimension, &NCMarker::SetDimension)
		.addProperty("position", &NCMarker::GetPosition, &NCMarker::SetPosition)
		.addProperty("rotation", &NCMarker::GetRotation, &NCMarker::SetRotation)
		.addProperty("velocity", &NCMarker::GetVelocity)
		.addProperty("model", &NCMarker::GetModel, &NCMarker::SetModel)
		.addProperty("alpha", &NCMarker::GetAlpha, &NCMarker::SetAlpha)
		.addCFunction("getColour", &NCMarker::GetColour)
		.addFunction("setColour", &NCMarker::SetColour)
		.addProperty("direction", &NCMarker::GetDirection, &NCMarker::SetDirection)
		.addProperty("scale", &NCMarker::GetScale, &NCMarker::SetScale)
		.addProperty("visible", &NCMarker::IsVisible, &NCMarker::SetVisible)
		.addCFunction("showFor", &NCMarker::ShowFor)
		.addCFunction("hideFor", &NCMarker::HideFor)
	.endClass()
	.beginNamespace("mp")
		.beginNamespace("markers")
			.addCFunction("at", &GetAtMarker)
			.addCFunction("new", &CreateMarker)
			.addFunction("exists", &Exists)
			.addCFunction("toArray", &ToArray)
			.addCFunction("forEach", &ForEach)
			.addFunction("size", &GetSize)
		.endNamespace()
	.endNamespace();
}