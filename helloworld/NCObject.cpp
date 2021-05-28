#include "NCALL.hpp"

NCObject::NCObject(rage::IEntity* entryEntity) {
	SetEntity(entryEntity);
}

void NCObject::Destroy() {
	GetObject()->Destroy();
	ClearEntity();
}

bool NCObject::operator==(NCObject* object) const {
	return object->GetEntity() == GetEntity();
}

bool NCObject::Exists(NCObject* object) {
	return object->entity ? true : false;
}

int NCObject::CreateObject(lua_State* state) {
	uint32_t model = 0;
	rage::vector3 vec;
	rage::vector3 rot;
	uint32_t dimension = 0;

	if (lua_isnumber(state, 1)) {
		model = (uint32_t)lua_tonumber(state, 1);
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

	if (lua_isuserdata(state, 3)) {
		NCVector3* vector = Userdata::get<NCVector3>(state, 3, false);
		rot = { vector->coord[0] , vector->coord[1] , vector->coord[2] };
	} else if (lua_istable(state, 3)) {
		LuaRef ref = LuaRef::fromStack(state, 3);

		float x = ref["x"];
		float y = ref["y"];
		float z = ref["z"];

		rot = { x , y , z };
	} else {
		return 0;
	}

	if (lua_isnumber(state, 4)) {
		dimension = (uint32_t)lua_tonumber(state, 4);
	}

	rage::IObject* object = RaluCore::getInstance().getMultiPlayer()->GetObjectPool().New(model, vec, rot, dimension);

	NCObject* scriptObject = object->External<NCObject>();
	push(state, scriptObject);
	return 1;
}

int NCObject::GetAtObject(lua_State* state) {
	LuaRef ref = LuaRef::fromStack(state, 1);

	if (!ref.isNumber()) {
		return 0;
	}

	rage::IObject* object = RaluCore::getInstance().getMultiPlayer()->GetObjectPool().GetAt(ref);

	if (!object) {
		return 0;
	}

	NCObject* scriptObject = object->External<NCObject>();

	push(state, scriptObject);
	return 1;
}

int NCObject::ForEach(lua_State* state) {
	LuaRef func = LuaRef::fromStack(state, 1);
	int size = 1;
	if (func.isFunction()) {
		for (rage::IObject* object : RaluCore::getInstance().getMultiPlayer()->GetObjectPool()) {
			func(object->External<NCObject>(), size);
			size++;
		}
	}
	return 0;

}

int NCObject::ToArray(lua_State* state) {
	LuaRef table = LuaRef::newTable(state);

	for (rage::IObject* object : RaluCore::getInstance().getMultiPlayer()->GetObjectPool()) {
		table.append(object->External<NCObject>());
	}

	push(state, table);
	return 1;
}

int NCObject::GetSize() {
	int size = 0;
	for (rage::IObject* object : RaluCore::getInstance().getMultiPlayer()->GetObjectPool()) { size++; }
	return size;
}

void NCObject::Register(LuaVM* rVM) {
	getGlobalNamespace(rVM->GetVM())
	.beginClass<NCObject>("NCObject")
		.addFunction("__eq", &NCObject::operator==)
		.addProperty("id", &NCObject::GetId)
		.addProperty("type", &NCObject::GetType)
		.addFunction("destroy", &NCObject::Destroy)
		.addProperty("dimension", &NCObject::GetDimension, &NCObject::SetDimension)
		.addProperty("position", &NCObject::GetPosition, &NCObject::SetPosition)
		.addProperty("rotation", &NCObject::GetRotation, &NCObject::SetRotation)
		.addProperty("velocity", &NCObject::GetVelocity)
		.addProperty("model", &NCObject::GetModel, &NCObject::SetModel)
		.addProperty("alpha", &NCObject::GetAlpha, &NCObject::SetAlpha)
	.endClass()
	.beginNamespace("mp")
		.beginNamespace("objects")
			.addCFunction("at", &GetAtObject)
			.addCFunction("new", &CreateObject)
			.addFunction("exists", &Exists)
			.addCFunction("toArray", &ToArray)
			.addCFunction("forEach", &ForEach)
			.addFunction("size", &GetSize)
		.endNamespace()
	.endNamespace();
}