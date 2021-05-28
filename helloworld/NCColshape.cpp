#include "NCALL.hpp"

NCColshape::NCColshape(rage::IEntity* entryEntity) {
	SetEntity(entryEntity);
}

void NCColshape::Destroy() {
	GetColshape()->Destroy();
	ClearEntity();
}

bool NCColshape::IsPointWithin(NCVector3* pos) const {
	rage::vector3 vec = { pos->coord[0], pos->coord[1],pos->coord[2] };
	return GetColshape()->IsPointWithin(vec);
}

uint8_t NCColshape::GetShapeType() const {
	return (uint8_t)GetColshape()->GetShapeType();
}

bool NCColshape::operator==(NCColshape* colshape) const {
	return colshape->GetEntity() == GetEntity();
}

bool NCColshape::Exists(NCColshape* colshape) {
	if (colshape->entity) {
		return true;
	}
	else {
		return false;
	}
}

int NCColshape::CreateColshapeCircle(lua_State* state) {
	float x;
	float y;
	float radius;
	uint32_t dimension = 0;

	if (lua_isnumber(state, 1)) {
		x = (float)lua_tonumber(state, 1);
	} else {
		return 0;
	}

	if (lua_isnumber(state, 2)) {
		y = (float)lua_tonumber(state, 2);
	} else {
		return 0;
	}

	rage::vector2 vec = { x, y };

	if (lua_isnumber(state, 3)) {
		radius = (float)lua_tonumber(state, 3);
	} else {
		return 0;
	}


	if (lua_isnumber(state, 4)) {
		dimension = (uint32_t)lua_tonumber(state, 3);
	}

	rage::IColshape* colshape = RaluCore::getInstance().getMultiPlayer()->GetColshapePool().NewCircle(vec, radius, dimension);

	NCColshape* scriptColshape = colshape->External<NCColshape>();
	push(state, scriptColshape);
	return 1;
}

int NCColshape::CreateColshapeSphere(lua_State* state) {
	rage::vector3 vec;
	float radius;
	uint32_t dimension = 0;

	if (lua_isuserdata(state, 1)) {
		NCVector3* vector = Userdata::get<NCVector3>(state, 1, false);

		vec = { vector->coord[0] , vector->coord[1] , vector->coord[2] };

	} else if (lua_istable(state, 1)) {
		LuaRef ref = LuaRef::fromStack(state, 1);

		float x = ref["x"];
		float y = ref["y"];
		float z = ref["z"];

		vec = { x , y , z };
	} else {
		return 0;
	}


	if (lua_isnumber(state, 2)) {
		radius = (float)lua_tonumber(state, 2);
	}
	else {
		return 0;
	}


	if (lua_isnumber(state, 3)) {
		dimension = (uint32_t)lua_tonumber(state, 3);
	}

	rage::IColshape* colshape = RaluCore::getInstance().getMultiPlayer()->GetColshapePool().NewSphere(vec, radius, dimension);

	NCColshape* scriptColshape = colshape->External<NCColshape>();
	push(state, scriptColshape);
	return 1;
}

int NCColshape::CreateColshapeTube(lua_State* state) {
	rage::vector3 vec;
	float radius;
	float height;
	uint32_t dimension = 0;

	if (lua_isuserdata(state, 1)) {
		NCVector3* vector = Userdata::get<NCVector3>(state, 1, false);

		vec = { vector->coord[0] , vector->coord[1] , vector->coord[2] };

	} else if (lua_istable(state, 1)) {
		LuaRef ref = LuaRef::fromStack(state, 1);

		float x = ref["x"];
		float y = ref["y"];
		float z = ref["z"];

		vec = { x , y , z };
	} else {
		return 0;
	}


	if (lua_isnumber(state, 2)) {
		radius = (float)lua_tonumber(state, 2);
	} else {
		return 0;
	}

	if (lua_isnumber(state, 3)) {
		height = (float)lua_tonumber(state, 3);
	} else {
		return 0;
	}


	if (lua_isnumber(state, 4)) {
		dimension = (uint32_t)lua_tonumber(state, 4);
	}

	rage::IColshape* colshape = RaluCore::getInstance().getMultiPlayer()->GetColshapePool().NewTube(vec, radius, height, dimension);

	NCColshape* scriptColshape = colshape->External<NCColshape>();
	push(state, scriptColshape);
	return 1;
}

int NCColshape::CreateColshapeRectangle(lua_State* state) {
	float x;
	float y;
	float radius;
	float height;
	uint32_t dimension = 0;

	if (lua_isnumber(state, 1)) {
		x = (float)lua_tonumber(state, 1);
	} else {
		return 0;
	}

	if (lua_isnumber(state, 2)) {
		y = (float)lua_tonumber(state, 2);
	} else {
		return 0;
	}

	rage::vector2 vec = { x, y };

	if (lua_isnumber(state, 3)) {
		radius = (float)lua_tonumber(state, 3);
	} else {
		return 0;
	}

	if (lua_isnumber(state, 3)) {
		height = (float)lua_tonumber(state, 3);
	} else {
		return 0;
	}

	rage::vector2 size = { radius, height };


	if (lua_isnumber(state, 4)) {
		dimension = (uint32_t)lua_tonumber(state, 3);
	}

	rage::IColshape* colshape = RaluCore::getInstance().getMultiPlayer()->GetColshapePool().NewRectangle(vec, size, dimension);

	NCColshape* scriptColshape = colshape->External<NCColshape>();
	push(state, scriptColshape);
	return 1;
}

int NCColshape::CreateColshapeCube(lua_State* state) {

	rage::vector3 vec;
	rage::vector3 size;
	uint32_t dimension = 0;

	if (lua_isuserdata(state, 1)) {
		NCVector3* vector = Userdata::get<NCVector3>(state, 1, false);

		vec = { vector->coord[0] , vector->coord[1] , vector->coord[2] };

	} else if (lua_istable(state, 1)) {
		LuaRef ref = LuaRef::fromStack(state, 1);

		float x = ref["x"];
		float y = ref["y"];
		float z = ref["z"];

		vec = { x , y , z };
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

	if (lua_isnumber(state, 3)) {
		dimension = (uint32_t)lua_tonumber(state, 3);
	}

	rage::IColshape* colshape = RaluCore::getInstance().getMultiPlayer()->GetColshapePool().NewCube(vec, size, dimension);

	NCColshape* scriptColshape = colshape->External<NCColshape>();
	push(state, scriptColshape);
	return 1;
}

int NCColshape::GetAtColshape(lua_State* state) {
	LuaRef ref = LuaRef::fromStack(state, 1);

	if (!ref.isNumber()) {
		return 0;
	}

	rage::IColshape* colshape = RaluCore::getInstance().getMultiPlayer()->GetColshapePool().GetAt(ref);

	if (!colshape) {
		return 0;
	}

	NCColshape* scriptColshape = colshape->External<NCColshape>();

	push(state, scriptColshape);
	return 1;
}

int NCColshape::ForEach(lua_State* state) {
	LuaRef func = LuaRef::fromStack(state, 1);
	int size = 1;
	if (func.isFunction()) {
		for (rage::IColshape* colshape : RaluCore::getInstance().getMultiPlayer()->GetColshapePool()) {
			func(colshape->External<NCColshape>(), size);
			size++;
		}
	}
	return 0;

}

int NCColshape::ToArray(lua_State* state) {
	LuaRef table = LuaRef::newTable(state);

	for (rage::IColshape* colshape : RaluCore::getInstance().getMultiPlayer()->GetColshapePool()) {
		table.append(colshape->External<NCColshape>());
	}

	push(state, table);
	return 1;
}

int NCColshape::GetSize() {
	int size = 0;
	for (rage::IColshape* colshape : RaluCore::getInstance().getMultiPlayer()->GetColshapePool()) { size++; }
	return size;
}

void NCColshape::Register(LuaVM* rVM) {
	getGlobalNamespace(rVM->GetVM())
	.beginClass<NCColshape>("NCColshape")
		.addFunction("__eq", &NCColshape::operator==)
		.addProperty("id", &NCColshape::GetId)
		.addProperty("type", &NCColshape::GetType)
		.addFunction("destroy", &NCColshape::Destroy)
		.addProperty("dimension", &NCColshape::GetDimension, &NCColshape::SetDimension)
		.addProperty("position", &NCColshape::GetPosition, &NCColshape::SetPosition)
		.addProperty("rotation", &NCColshape::GetRotation, &NCColshape::SetRotation)
		.addProperty("velocity", &NCColshape::GetVelocity)
		.addProperty("model", &NCColshape::GetModel, &NCColshape::SetModel)
		.addProperty("alpha", &NCColshape::GetAlpha, &NCColshape::SetAlpha)
		.addFunction("isPointWithin", &NCColshape::IsPointWithin)
		.addProperty("shapeType", &NCColshape::GetShapeType)
	.endClass()
	.beginNamespace("mp")
		.beginNamespace("colshapes")
			.addCFunction("at", &GetAtColshape)
			.addCFunction("newCircle", &CreateColshapeCircle)
			.addCFunction("newSphere", &CreateColshapeSphere)
			.addCFunction("newTube", &CreateColshapeTube)
			.addCFunction("newRectangle", &CreateColshapeRectangle)
			.addCFunction("newCuboid", &CreateColshapeCube)
			.addFunction("exists", &Exists)
			.addCFunction("toArray", &ToArray)
			.addCFunction("forEach", &ForEach)
			.addFunction("size", &GetSize)
		.endNamespace()
	.endNamespace();
}