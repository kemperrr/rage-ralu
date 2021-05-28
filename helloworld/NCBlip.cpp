#include "NCBlip.hpp"

NCBlip::NCBlip(rage::IEntity* entryEntity) {
	SetEntity(entryEntity);
}

uint16_t NCBlip::GetId() const {
	return entity->GetId();
}

uint32_t NCBlip::GetDimension() const {
	return entity->GetDimension();
}

void NCBlip::SetDimension(uint32_t dimension) {
	entity->SetDimension(dimension);
}

NCVector3* NCBlip::GetPosition() const {
	rage::vector3 vec = entity->GetPosition();
	return new NCVector3(vec.x, vec.y, vec.z);
}

void NCBlip::SetPosition(NCVector3* pos) {
	rage::vector3 vec = { pos->coord[0], pos->coord[1], pos->coord[2] };
	entity->SetPosition(vec);
}

NCVector3* NCBlip::GetRotation() const {
	rage::vector3 vec = entity->GetRotation();
	return new NCVector3(vec.x, vec.y, vec.z);
}

void NCBlip::SetRotation(NCVector3* rot) {
	rage::vector3 vec = { rot->coord[0], rot->coord[1], rot->coord[2] };
	entity->SetRotation(vec);
}

uint32_t NCBlip::GetModel() const {
	return entity->GetModel();
}

void NCBlip::SetModel(uint32_t model) {
	entity->SetModel(model);
}

NCVector3* NCBlip::GetVelocity() const {
	rage::vector3 vec = entity->GetVelocity();
	return new NCVector3(vec.x, vec.y, vec.z);
}

void NCBlip::Destroy() {
	GetBlip()->Destroy();
	ClearEntity();
}

float NCBlip::GetRadius() const {
	return GetBlip()->GetRadius();
}

uint8_t NCBlip::GetMode() const {
	return (uint8_t)GetBlip()->GetMode();
}

int NCBlip::RouteFor(lua_State* state) {

	uint8_t colour = 0;
	float scale = 1;

	std::vector<rage::IPlayer*> players;

	if (lua_istable(state, 2)) {

		LuaRef playersTable = LuaRef::fromStack(state, 2);

		for (Iterator iter(playersTable); !iter.isNil(); ++iter)
		{
			LuaRef key = iter.key();
			LuaRef val = *iter;

			if (val.isUserdata()) {
				NCPlayer* player = val;
				if (player->GetType() == "player") {
					players.push_back(player->GetPlayer());
				}
			}
		}
	} else {
		return 0;
	}
	
	LuaRef colorSettings = LuaRef::fromStack(state, 3);
	LuaRef scaleSettings = LuaRef::fromStack(state, 4);

	if (colorSettings.isNumber()) {
		colour = colorSettings;
	}

	if (scaleSettings.isNumber()) {
		scale = scaleSettings;
	}

	GetBlip()->RouteFor(players, colour, scale);

	return 0;
}

int NCBlip::UnrouteFor(lua_State* state) {

	std::vector<rage::IPlayer*> players;

	if (lua_istable(state, 2)) {

		LuaRef playersTable = LuaRef::fromStack(state, 2);

		for (Iterator iter(playersTable); !iter.isNil(); ++iter)
		{
			LuaRef key = iter.key();
			LuaRef val = *iter;

			if (val.isUserdata()) {
				NCPlayer* player = val;
				if (player->GetType() == "player") {
					players.push_back(player->GetPlayer());
				}
			}
		}
	} else {
		return 0;
	}

	GetBlip()->UnrouteFor(players);

	return 0;
}

uint8_t NCBlip::GetColour() const {
	return GetBlip()->GetColour();
}

void NCBlip::SetColour(uint8_t colour) {
	GetBlip()->SetColour(colour);
}

uint8_t NCBlip::GetAlpha() const {
	return GetBlip()->GetAlpha();
}

void NCBlip::SetAlpha(uint8_t alpha) {
	GetBlip()->SetAlpha(alpha);
}

float NCBlip::GetScale() const {
	return GetBlip()->GetScale();
}

void NCBlip::SetScale(float scale) {
	GetBlip()->SetScale(scale);
}

std::string NCBlip::GetName() const {
	return GetBlip()->GetName();
}

void NCBlip::SetName(std::string name) {
	GetBlip()->SetName(name);
}

bool NCBlip::operator==(NCBlip* blip) const {
	return blip->GetEntity() == GetEntity();
}

int NCBlip::CreateBlip(lua_State* state) {
	uint32_t sprite = 0;
	uint32_t dimension = 0;
	rage::vector3 vec;

	if (lua_isnumber(state, 1)) {
		sprite = (uint32_t)lua_tonumber(state, 1);
	} else {
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
	} else {
		return 0;
	}

	if (lua_isnumber(state, 3)) {
		dimension = (uint32_t)lua_tonumber(state, 3);
	}

	rage::IBlip* blip = RaluCore::getInstance().getMultiPlayer()->GetBlipPool().New(sprite, vec, dimension);

	NCBlip* scriptBlip = blip->External<NCBlip>();
	push(state, scriptBlip);
	return 1;
	
}

int NCBlip::CreateBlipStreamed(lua_State* state) {

	uint32_t sprite = 0;
	uint32_t dimension = 0;
	float streamRange;
	rage::vector3 vec;

	if (lua_isnumber(state, 1)) {
		sprite = (uint32_t)lua_tonumber(state, 1);
	}
	else {
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

	if (lua_isnumber(state, 3)) {
		streamRange = (float)lua_tonumber(state, 3);
	} else {
		return 0;
	}

	if (lua_isnumber(state, 4)) {
		dimension = (uint32_t)lua_tonumber(state, 4);
	}

	rage::IBlip* blip = RaluCore::getInstance().getMultiPlayer()->GetBlipPool().NewStreamed(sprite, vec, streamRange, dimension);

	NCBlip* scriptBlip = blip->External<NCBlip>();
	push(state, scriptBlip);
	return 1;
}

int NCBlip::GetAtBlip(lua_State* state) {
	LuaRef ref = LuaRef::fromStack(state, 1);

	if (!ref.isNumber()) {
		return 0;
	}

	rage::IBlip* blip = RaluCore::getInstance().getMultiPlayer()->GetBlipPool().GetAt(ref);

	if (!blip) {
		return 0;
	}

	NCBlip* scriptBlip = blip->External<NCBlip>();

	push(state, scriptBlip);
	return 1;
}

bool NCBlip::Exists(NCBlip* blip) {
	return blip->entity ? true : false;
}

int NCBlip::ForEach(lua_State* state) {
	LuaRef func = LuaRef::fromStack(state, 1);
	int size = 1;
	if (func.isFunction()) {
		for (rage::IObject* object : RaluCore::getInstance().getMultiPlayer()->GetObjectPool()) {
			func(object->External<NCBlip>(), size);
			size++;
		}
	}
	return 0;

}

int NCBlip::ToArray(lua_State* state) {
	LuaRef table = LuaRef::newTable(state);

	for (rage::IObject* object : RaluCore::getInstance().getMultiPlayer()->GetObjectPool()) {
		table.append(object->External<NCBlip>());
	}

	push(state, table);
	return 1;
}

int NCBlip::GetSize() {
	int size = 0;
	for (rage::IObject* object : RaluCore::getInstance().getMultiPlayer()->GetObjectPool()) { size++; }
	return size;
}

void NCBlip::Register(LuaVM* rVM) {
	getGlobalNamespace(rVM->GetVM())
	.beginClass<NCBlip>("NCBlip")
		.addFunction("__eq", &NCBlip::operator==)
		.addProperty("id", &NCBlip::GetId)
		.addProperty("type", &NCBlip::GetType)
		.addFunction("destroy", &NCBlip::Destroy)
		.addProperty("dimension", &NCBlip::GetDimension, &NCBlip::SetDimension)
		.addProperty("position", &NCBlip::GetPosition, &NCBlip::SetPosition)
		.addProperty("rotation", &NCBlip::GetRotation, &NCBlip::SetRotation)
		.addProperty("velocity", &NCBlip::GetVelocity)
		.addProperty("model", &NCBlip::GetModel, &NCBlip::SetModel)
		.addProperty("alpha", &NCBlip::GetAlpha, &NCBlip::SetAlpha)
		.addProperty("radius", &NCBlip::GetRadius)
		.addProperty("mode", &NCBlip::GetMode)
		.addCFunction("routeFor", &NCBlip::RouteFor)
		.addCFunction("unrouteFor", &NCBlip::UnrouteFor)
		.addProperty("colour", &NCBlip::GetColour, &NCBlip::SetColour)
		.addProperty("scale", &NCBlip::GetScale, &NCBlip::SetScale)
		.addProperty("name", &NCBlip::GetName, &NCBlip::SetName)
	.endClass()
	.beginNamespace("mp")
		.beginNamespace("blips")
			.addCFunction("at", &GetAtBlip)
			.addCFunction("new", &CreateBlip)
			.addCFunction("newStreamed", &CreateBlipStreamed)
			.addFunction("exists", &Exists)
			.addCFunction("toArray", &ToArray)
			.addCFunction("forEach", &ForEach)
			.addFunction("size", &GetSize)
		.endNamespace()
	.endNamespace();
}