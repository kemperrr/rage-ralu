#include "NCALL.hpp"

#define IS_ENTITY_VALID GetVehicle()->entity ? true : false

#define d_ENTITY_VALID if (!GetVehicle()) {\
							std::cout << "expected multiplayer object" << std::endl;

#define D_ENTITY_END }

NCVehicle::NCVehicle(rage::IEntity* entryEntity) {
	SetEntity(entryEntity);
}

void NCVehicle::Destroy() {

	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return;
	}

	GetVehicle()->Destroy();
	ClearEntity();
}

bool NCVehicle::IsSirenActive() const {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return NULL;
	}

	return GetVehicle()->IsSirenActive();
}

void NCVehicle::SetSirenActive(bool toggle) {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return;
	}

	GetVehicle()->SetSirenActive(toggle);
}

bool NCVehicle::IsHornActive() const {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return NULL;
	}

	return GetVehicle()->IsHornActive();
}

bool NCVehicle::AreHighbeamsActive() const {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return NULL;
	}

	return GetVehicle()->AreHighbeamsActive();
}

void NCVehicle::SetHighbeamsActive(bool toggle) {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return;
	}

	GetVehicle()->SetHighbeamsActive(toggle);
}

bool NCVehicle::AreLightsActive() const {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return NULL;
	}

	return GetVehicle()->AreLightsActive();
}

void NCVehicle::SetLightsActive(bool toggle) {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return;
	}

	GetVehicle()->SetLightsActive(toggle);
}

bool NCVehicle::IsEngineActive() const {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return NULL;
	}

	return GetVehicle()->IsEngineActive();
}

void NCVehicle::SetEngineActive(bool toggle) {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return;
	}

	GetVehicle()->SetEngineActive(toggle);
}

bool NCVehicle::IsRocketBoostActive() const {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return NULL;
	}

	return GetVehicle()->IsRocketBoostActive();
}

bool NCVehicle::IsBrakeActive() const {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return NULL;
	}

	return GetVehicle()->IsBrakeActive();
}

float NCVehicle::GetSteerAngle() const {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return NULL;
	}

	return GetVehicle()->GetSteerAngle();
}

float NCVehicle::GetGasPedalState() const {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return NULL;
	}

	return GetVehicle()->GetGasPedalState();
}

float NCVehicle::GetEngineHealth() const {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return NULL;
	}

	return GetVehicle()->GetEngineHealth();
}

float NCVehicle::GetBodyHealth() const {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return NULL;
	}

	return GetVehicle()->GetBodyHealth();
}

NCPlayer* NCVehicle::GetOccupant(uint8_t seat) const {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return nullptr;
	}

	rage::IPlayer* player = GetVehicle()->GetOccupant(seat);

	if (player) {
		NCPlayer* scriptPlayer = player->External<NCPlayer>();
		return scriptPlayer;
	}

	return nullptr;
}

int NCVehicle::GetOccupants(lua_State* state) {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return NULL;
	}

	std::vector<rage::IPlayer*> players = GetVehicle()->GetOccupants();

	LuaRef table = LuaRef::newTable(state);

	for (auto player : players) {
		NCPlayer* scriptPlayer = player->External<NCPlayer>();
		table.append(scriptPlayer);
	}

	push(state, table);
	return 1;
}

void NCVehicle::SetOccupant(uint8_t seat, NCPlayer* player) {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return;
	}

	if (!player->GetPlayer()) {
		return;
	}

	GetVehicle()->SetOccupant(seat, player->GetPlayer());
	return;
}

bool NCVehicle::IsLocked() const {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return NULL;
	}

	return GetVehicle()->IsLocked();
}

void NCVehicle::Lock(bool toggle) {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return;
	}

	GetVehicle()->Lock(toggle);
}

bool NCVehicle::IsDead() const {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return NULL;
	}

	return GetVehicle()->IsDead();
}

void NCVehicle::Explode() {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return;
	}

	GetVehicle()->Explode();
}

void NCVehicle::Spawn(NCVector3* pos, float heading) {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return;
	}

	rage::vector3 vec = { pos->coord[0], pos->coord[1], pos->coord[2] };
	GetVehicle()->Spawn(vec, heading);
}

uint8_t NCVehicle::GetMod(uint8_t id) const {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return NULL;
	}

	return GetVehicle()->GetMod(id);
}

void NCVehicle::SetMod(uint8_t id, uint8_t mod) {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return;
	}

	GetVehicle()->SetMod(id, mod);
}

bool NCVehicle::AreNeonsEnabled() const {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return NULL;
	}

	return GetVehicle()->AreNeonsEnabled();
}

void NCVehicle::EnableNeons(bool toggle) {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return;
	}

	GetVehicle()->EnableNeons(toggle);
}

void NCVehicle::SetNeonsColour(uint8_t r, uint8_t g, uint8_t b) {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return;
	}

	GetVehicle()->SetNeonsColour(r, g, b);
}

int NCVehicle::GetNeonsColour(lua_State* state) {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return NULL;
	}

	rage::rgb_t colour = GetVehicle()->GetNeonsColour();

	push(state, colour.r);
	push(state, colour.g);
	push(state, colour.b);
	return 3;
}

void NCVehicle::Repair() {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return;
	}

	GetVehicle()->Repair();
}

int NCVehicle::GetColourRGB(lua_State* state) {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return NULL;
	}

	LuaRef id = LuaRef::fromStack(state, 2);

	if (!id.isNumber()) {
		return 0;
	}

	rage::rgb_t colour = GetVehicle()->GetColourRGB((uint8_t)id);
	push(state, colour.r);
	push(state, colour.g);
	push(state, colour.b);
	return 3;
}

uint8_t NCVehicle::GetColour(uint8_t id) const {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return NULL;
	}

	return GetVehicle()->GetColour(id);
}

uint8_t NCVehicle::GetPaint(uint8_t id) const {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return NULL;
	}

	return GetVehicle()->GetPaint(id);
}

void NCVehicle::SetColourRGB(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2) {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return;
	}

	rage::rgb_t primary = { r1, g1, b1 };
	rage::rgb_t secondary = { r2, g2, b2 };

	GetVehicle()->SetColourRGB(primary, secondary);
}

void NCVehicle::SetColour(uint8_t primary, uint8_t secondary) {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return;
	}

	GetVehicle()->SetColour(primary, secondary);
}

void NCVehicle::SetPaint(uint8_t type1, uint8_t colour1, uint8_t type2, uint8_t colour2) {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return;
	}

	rage::paintInfo_t primary = { type1, colour1 };
	rage::paintInfo_t secondary = { type2, colour2 };
	GetVehicle()->SetPaint(primary, secondary);
}

uint8_t NCVehicle::GetMaterialType() const {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return NULL;
	}

	return (uint8_t)GetVehicle()->GetMaterialType();
}

std::string NCVehicle::GetNumberPlate() const {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return NULL;
	}

	return GetVehicle()->GetNumberPlate();
}

void NCVehicle::SetNumberPlate(const std::string numberPlate) {
	if (!GetVehicle()) {
		std::cout << "expected multiplayer object" << std::endl;
		return;
	}

	GetVehicle()->SetNumberPlate(numberPlate);
}

bool NCVehicle::operator==(NCVehicle* vehicle) const {
	if (!GetVehicle()) {
		return false;
	}

	return vehicle->GetVehicle() == GetVehicle();
}

int NCVehicle::CreateVehicle(lua_State* state) {
	uint32_t model;
	rage::vector3 vec;
	float heading = 0;
	int dimension = 0;
	int ColorPrimary = 0;
	int ColorSecondary = 0;

	if (lua_isnumber(state, 1)) {
		model = (uint32_t)lua_tonumber(state, 1);
	}
	else if (lua_isstring(state, 1)) {
		size_t length = 0;
		const char* szTmp = lua_tolstring(state, 1, &length);
		model = Utility::joaat(szTmp);
	}
	else {
		return -1;
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
		return -1;
	}

	if (lua_istable(state, 3)) {
		LuaRef ref = LuaRef::fromStack(state, 3);

		if (ref["heading"].isNumber()) {
			heading = ref["heading"];
		}

		if (ref["dimension"].isNumber()) {
			dimension = ref["dimension"];
		}

		if (ref["color"].isTable()) {

			LuaRef refColor = ref["color"];

			if (refColor["primary"].isNumber()) {
				ColorPrimary = refColor["primary"];

			}
			if (refColor["secondary"].isNumber()) {
				ColorSecondary = refColor["secondary"];
			}

			if (refColor["rgba"].isTable())
			{
				LuaRef refRGBA = refColor["rgba"];

			}
		}

	}

	rage::IVehicle* veh = RaluCore::getInstance().getMultiPlayer()->GetVehiclePool().New(model, vec, heading, dimension);
	veh->SetColour(ColorPrimary, ColorSecondary);

	model = NULL;
	heading = NULL;
	dimension = NULL;
	NCVehicle* scriptCheckpoint = veh->External<NCVehicle>();
	push(state, scriptCheckpoint);
	return 1;
}

int NCVehicle::GetAtVehicle(lua_State* state) {
	LuaRef ref = LuaRef::fromStack(state, 1);

	if (!ref.isNumber()) {
		return 0;
	}

	rage::IVehicle* vehicle = RaluCore::getInstance().getMultiPlayer()->GetVehiclePool().GetAt(ref);

	if (!vehicle) {
		return 0;
	}

	NCVehicle* scriptVehicle = vehicle->External<NCVehicle>();

	push(state, scriptVehicle);
	return 1;
}

bool NCVehicle::Exists(NCVehicle* vehicle) {
	return vehicle->entity ? true : false;
}

int NCVehicle::ForEach(lua_State* state) {
	LuaRef func = LuaRef::fromStack(state, 1);
	int size = 1;
	if (func.isFunction()) {
		for (rage::IVehicle* vehicle : RaluCore::getInstance().getMultiPlayer()->GetVehiclePool()) {
			func(vehicle->External<NCVehicle>(), size);
			size++;
		}
	}
	return 0;

}

int NCVehicle::ToArray(lua_State* state) {
	LuaRef table = LuaRef::newTable(state);

	for (rage::IVehicle* vehicle : RaluCore::getInstance().getMultiPlayer()->GetVehiclePool()) {
		table.append(vehicle->External<NCVehicle>());
	}

	push(state, table);
	return 1;
}

int NCVehicle::GetSize() {
	int size = 0;
	for (rage::IVehicle* vehicle : RaluCore::getInstance().getMultiPlayer()->GetVehiclePool()) { size ++; }
	return size;
}

void NCVehicle::Register(LuaVM* rVM) {
	getGlobalNamespace(rVM->GetVM())
	.beginClass<NCVehicle>("NCVehicle")
		.addFunction("__eq", &NCVehicle::operator==)
		.addProperty("id", &NCVehicle::GetId)
		.addProperty("type", &NCVehicle::GetType)
		.addFunction("destroy", &NCVehicle::Destroy)
		.addProperty("dimension", &NCVehicle::GetDimension, &NCVehicle::SetDimension)
		.addProperty("position", &NCVehicle::GetPosition, &NCVehicle::SetPosition)
		.addProperty("rotation", &NCVehicle::GetRotation, &NCVehicle::SetRotation) // поворачивает всегда в одну сторону
		.addProperty("velocity", &NCVehicle::GetVelocity) // возвращает всего 0
		.addProperty("model", &NCVehicle::GetModel, &NCVehicle::SetModel)
		.addProperty("alpha", &NCVehicle::GetAlpha, &NCVehicle::SetAlpha)
		.addProperty("siren", &NCVehicle::IsSirenActive, &NCVehicle::SetSirenActive)
		.addProperty("horn", &NCVehicle::IsHornActive)
		.addProperty("highbeams", &NCVehicle::AreHighbeamsActive, &NCVehicle::SetHighbeamsActive)
		.addProperty("lights", &NCVehicle::AreLightsActive, &NCVehicle::SetLightsActive)
		.addProperty("engine", &NCVehicle::IsEngineActive, &NCVehicle::SetEngineActive)
		.addProperty("rocketBoost", &NCVehicle::IsRocketBoostActive)
		.addProperty("brake", &NCVehicle::IsBrakeActive)
		.addProperty("steerAngle", &NCVehicle::GetSteerAngle)
		.addProperty("gasState", &NCVehicle::GetGasPedalState)
		.addProperty("engineHealth", &NCVehicle::GetEngineHealth)
		.addProperty("bodyHealth", &NCVehicle::GetBodyHealth)
		.addFunction("getOccupant", &NCVehicle::GetOccupant)
		.addCFunction("getOccupants", &NCVehicle::GetOccupants)
		.addFunction("setOccupant", &NCVehicle::SetOccupant)
		.addProperty("locked", &NCVehicle::IsLocked, &NCVehicle::Lock)
		.addProperty("dead", &NCVehicle::IsDead)
		.addFunction("explode", &NCVehicle::Explode)
		.addFunction("spawn", &NCVehicle::Spawn)
		.addFunction("getMod", &NCVehicle::GetMod)
		.addFunction("setMod", &NCVehicle::SetMod)
		.addProperty("neonEnabled", &NCVehicle::AreNeonsEnabled, &NCVehicle::EnableNeons)
		.addFunction("setNeonsColour", &NCVehicle::SetNeonsColour)
		.addCFunction("getNeonsColour", &NCVehicle::GetNeonsColour)
		.addFunction("repair", &NCVehicle::Repair)
		.addCFunction("getColourRGB", &NCVehicle::GetColourRGB)
		.addFunction("getColour", &NCVehicle::GetColour)
		.addFunction("getPaint", &NCVehicle::GetPaint)
		.addFunction("setColourRGB", &NCVehicle::SetColourRGB)
		.addFunction("setColour", &NCVehicle::SetColour)
		.addFunction("setPaint", &NCVehicle::SetPaint)
		.addProperty("materialType", &NCVehicle::GetMaterialType)
		.addProperty("numberPlate", &NCVehicle::GetNumberPlate, &NCVehicle::SetNumberPlate)
	.endClass()
	.beginNamespace("mp")
		.beginNamespace("vehicles")
			.addCFunction("new", &CreateVehicle)
			.addCFunction("at", &GetAtVehicle)
			.addFunction("exists", &Exists)
			.addCFunction("toArray", &ToArray)
			.addCFunction("forEach", &ForEach)
			.addFunction("size", &GetSize)
		.endNamespace()
	.endNamespace();
}