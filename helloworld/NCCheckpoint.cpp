#include "NCALL.hpp"

NCCheckpoint::NCCheckpoint(rage::IEntity* entryEntity) {
	SetEntity(entryEntity);
}

uint16_t NCCheckpoint::GetId() const {
	return entity->GetId();
}

uint32_t NCCheckpoint::GetDimension() const {
	return entity->GetDimension();
}

void NCCheckpoint::SetDimension(uint32_t dimension) {
	entity->SetDimension(dimension);
}

NCVector3* NCCheckpoint::GetPosition() const {
	rage::vector3 vec = entity->GetPosition();
	return new NCVector3(vec.x, vec.y, vec.z);
}

void NCCheckpoint::SetPosition(NCVector3* pos) {
	rage::vector3 vec = { pos->coord[0], pos->coord[1], pos->coord[2] };
	entity->SetPosition(vec);
}

NCVector3* NCCheckpoint::GetRotation() const {
	rage::vector3 vec = entity->GetRotation();
	return new NCVector3(vec.x, vec.y, vec.z);
}

void NCCheckpoint::SetRotation(NCVector3* rot) {
	rage::vector3 vec = { rot->coord[0], rot->coord[1], rot->coord[2] };
	entity->SetRotation(vec);
}

uint32_t NCCheckpoint::GetModel() const {
	return entity->GetModel();
}

void NCCheckpoint::SetModel(uint32_t model) {
	entity->SetModel(model);
}

NCVector3* NCCheckpoint::GetVelocity() const {
	rage::vector3 vec = entity->GetVelocity();
	return new NCVector3(vec.x, vec.y, vec.z);
}

uint8_t NCCheckpoint::GetAlpha() const {
	return entity->GetAlpha();
}

void NCCheckpoint::SetAlpha(uint8_t alpha) {
	entity->SetAlpha(alpha);
}

bool NCCheckpoint::Destroy() const {
	GetCheckpoint()->Destroy();
	return true;
}

int NCCheckpoint::GetColour(lua_State* state) {
	rage::rgba_t colour = GetCheckpoint()->GetColour();
	luabridge::push(state, colour.rgba[0]);
	luabridge::push(state, colour.rgba[1]);
	luabridge::push(state, colour.rgba[2]);
	luabridge::push(state, colour.rgba[3]);
	return 4;
}

void NCCheckpoint::SetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	GetCheckpoint()->SetColour(r, g, b, a);
}

NCVector3* NCCheckpoint::GetDirection() const {
	rage::vector3 vec = GetCheckpoint()->GetDirection();
	return new NCVector3(vec.x, vec.y, vec.z);
}

void NCCheckpoint::SetDirection(NCVector3* pos) {
	rage::vector3 vec = { pos->coord[0], pos->coord[1], pos->coord[2] };
	GetCheckpoint()->SetDirection(vec);
}

float NCCheckpoint::GetRadius() const {
	return GetCheckpoint()->GetRadius();
}

void NCCheckpoint::SetRadius(float radius) {
	GetCheckpoint()->SetRadius(radius);
}

bool NCCheckpoint::IsVisible() const {
	return GetCheckpoint()->IsVisible();
}

void NCCheckpoint::SetVisible(bool toggle) {
	GetCheckpoint()->SetVisible(toggle);
}

int NCCheckpoint::ShowFor(lua_State* state) {
	std::vector<rage::IPlayer*> players;

	for (int i = 2; i <= lua_gettop(state); i++) {
		NCPlayer* ref = Userdata::get<NCPlayer>(state, i, false);
		if (ref->GetType() == "player" && std::find(players.begin(), players.end(), ref->GetPlayer()) == players.end()) {
			players.push_back(ref->GetPlayer());
		}
	}

	GetCheckpoint()->ShowFor(players);
	return 0;
}

int NCCheckpoint::HideFor(lua_State* state) {
	std::vector<rage::IPlayer*> players;

	for (int i = 2; i <= lua_gettop(state); i++) {
		NCPlayer* ref = Userdata::get<NCPlayer>(state, i, false);
		if (ref->GetType() == "player" && std::find(players.begin(), players.end(), ref->GetPlayer()) == players.end()) {
			players.push_back(ref->GetPlayer());
		}
	}

	GetCheckpoint()->HideFor(players);
	return 0;
}

bool NCCheckpoint::operator==(NCCheckpoint* checkpoint) const {
	return checkpoint->GetEntity() == GetEntity();
}

int NCCheckpoint::CreateCheckpoint(lua_State* state) {
	uint8_t model = 0;
	uint32_t dimension = 0;
	bool defaultShow = true;
	float radius = 1.0;
	rage::vector3 vec;
	rage::vector3 dir;
	rage::rgba_t color;

	if (lua_isnumber(state, 1)) {
		model = (uint8_t)lua_tonumber(state, 1);
	}
	else {
		return 0;
	}

	if (lua_isuserdata(state, 2)) {
		NCVector3* vector = Userdata::get<NCVector3>(state, 2, false);

		vec = { vector->coord[0] , vector->coord[1] , vector->coord[2] };

	}
	else if (lua_istable(state, 2)) {
		LuaRef ref = LuaRef::fromStack(state, 2);

		float x = ref["x"];
		float y = ref["y"];
		float z = ref["z"];

		vec = { x , y , z };
	}
	else {
		return 0;
	}

	if (lua_isuserdata(state, 3)) {
		NCVector3* vector = Userdata::get<NCVector3>(state, 3, false);

		dir = { vector->coord[0] , vector->coord[1] , vector->coord[2] };

	}
	else if (lua_istable(state, 3)) {
		LuaRef ref = LuaRef::fromStack(state, 3);

		float x = ref["x"];
		float y = ref["y"];
		float z = ref["z"];

		dir = { x , y , z };
	}
	else {
		return 0;
	}

	if (lua_istable(state, 4)) {
		LuaRef ref = LuaRef::fromStack(state, 4);

		if (ref["radius"].isNumber()) {
			radius = ref["radius"];
		}

		if (ref["r"].isNumber()) {
			color.rgba[0] = ref["r"];
		}

		if (ref["g"].isNumber()) {
			color.rgba[1] = ref["g"];
		}

		if (ref["b"].isNumber()) {
			color.rgba[2] = ref["b"];
		}

		if (ref["a"].isNumber()) {
			color.rgba[3] = ref["a"];
		}

		if (ref["dimension"].isNumber()) {
			dimension = ref["dimension"];
		}

		if (ref["visible"].isBoolean()) {
			defaultShow = ref["visible"];
		}
	}

	rage::ICheckpoint* checkpoint = RaluCore::getInstance().getMultiPlayer()->GetCheckpointPool().New(model, vec, dir, radius, color, defaultShow, dimension);

	model = NULL;
	dimension = NULL;
	radius = NULL;
	defaultShow = NULL;
	dimension = NULL;

	NCCheckpoint* scriptCheckpoint = checkpoint->External<NCCheckpoint>();
	push(state, scriptCheckpoint);
	return 1;
}

int NCCheckpoint::GetAtCheckpoint(lua_State* state) {
	LuaRef ref = LuaRef::fromStack(state, 1);

	if (!ref.isNumber()) {
		return 0;
	}

	rage::ICheckpoint* checkpoint = RaluCore::getInstance().getMultiPlayer()->GetCheckpointPool().GetAt(ref);

	if (!checkpoint) {
		return 0;
	}

	NCCheckpoint* scriptCheckpoint = checkpoint->External<NCCheckpoint>();

	push(state, scriptCheckpoint);
	return 1;
}

bool NCCheckpoint::Exists(NCCheckpoint* checkpoint) {
	return checkpoint->entity ? true : false;
}

int NCCheckpoint::ForEach(lua_State* state) {
	LuaRef func = LuaRef::fromStack(state, 1);
	int size = 1;
	if (func.isFunction()) {
		for (rage::ICheckpoint* checkpoint : RaluCore::getInstance().getMultiPlayer()->GetCheckpointPool()) {
			func(checkpoint->External<NCCheckpoint>(), size);
			size++;
		}
	}
	return 0;

}

int NCCheckpoint::ToArray(lua_State* state) {
	LuaRef table = LuaRef::newTable(state);

	for (rage::ICheckpoint* checkpoint : RaluCore::getInstance().getMultiPlayer()->GetCheckpointPool()) {
		table.append(checkpoint->External<NCCheckpoint>());
	}

	push(state, table);
	return 1;
}

int NCCheckpoint::GetSize() {
	int size = 0;
	for (rage::ICheckpoint* checkpoint : RaluCore::getInstance().getMultiPlayer()->GetCheckpointPool()) { size++; }
	return size;
}

void NCCheckpoint::Register(LuaVM* rVM) {
	getGlobalNamespace(rVM->GetVM())
	.beginClass<NCCheckpoint>("NCCheckpoint")
		.addFunction("__eq", &NCCheckpoint::operator==)
		.addProperty("id", &NCCheckpoint::GetId)
		.addProperty("type", &NCCheckpoint::GetType)
		.addFunction("destroy", &NCCheckpoint::Destroy)
		.addProperty("dimension", &NCCheckpoint::GetDimension, &NCCheckpoint::SetDimension)
		.addProperty("position", &NCCheckpoint::GetPosition, &NCCheckpoint::SetPosition)
		.addProperty("rotation", &NCCheckpoint::GetRotation, &NCCheckpoint::SetRotation)
		.addProperty("velocity", &NCCheckpoint::GetVelocity)
		.addProperty("model", &NCCheckpoint::GetModel, &NCCheckpoint::SetModel)
		.addProperty("alpha", &NCCheckpoint::GetAlpha, &NCCheckpoint::SetAlpha)
		.addCFunction("getColour", &NCCheckpoint::GetColour)
		.addFunction("setColour", &NCCheckpoint::SetColour)
		.addProperty("direction", &NCCheckpoint::GetDirection, &NCCheckpoint::SetDirection)
		.addProperty("radius", &NCCheckpoint::GetRadius, &NCCheckpoint::SetRadius)
		.addProperty("visible", &NCCheckpoint::IsVisible, &NCCheckpoint::SetVisible)
		.addCFunction("showFor", &NCCheckpoint::ShowFor)
		.addCFunction("hideFor", &NCCheckpoint::HideFor)
	.endClass()
	.beginNamespace("mp")
		.beginNamespace("checkpoints")
			.addCFunction("at", &GetAtCheckpoint)
			.addCFunction("new", &CreateCheckpoint)
			.addFunction("exists", &Exists)
			.addCFunction("toArray", &ToArray)
			.addCFunction("forEach", &ForEach)
			.addFunction("size", &GetSize)
		.endNamespace()
	.endNamespace();
}
