#include "NCPlayer.hpp"

NCPlayer::NCPlayer(rage::IEntity* entryEntity) {
	SetEntity(entryEntity);
}

void NCPlayer::Kick(const char *reason) {
	GetPlayer()->Kick(reason);
}

void NCPlayer::Ban(const char *reason) {
	GetPlayer()->Ban(reason);
}

void NCPlayer::OutputChatBox(const std::string text) {
	std::u16string u16str(Utility::toU16String(text));

	GetPlayer()->OutputChatBox(u16str);
}

void NCPlayer::Notify(const std::string text) {
	std::u16string u16str(Utility::toU16String(text));
	GetPlayer()->Notify(u16str);
}

int NCPlayer::Spawn(lua_State* state) {
	rage::vector3 vec = { 0,0,0 };
	float heading = 0;

	if (!lua_isuserdata(state, 2)) {
		return 0;
	}

	NCVector3* vector = Userdata::get<NCVector3>(state, 2, false);

	vec = { vector->coord[0] , vector->coord[1] , vector->coord[2] };

	LuaRef ref = LuaRef::fromStack(state, 3);

	if (ref.isNumber()) {
		heading = ref;
	}

	GetPlayer()->Spawn(vec, heading);
	return 0;
}

void NCPlayer::PlayAnimation(std::string dict, std::string name, float speed, int flags) {
	GetPlayer()->PlayAnimation(dict, name, speed, flags);
}

void NCPlayer::PlayScenario(const std::string scenario) {
	GetPlayer()->PlayScenario(scenario);
}

void NCPlayer::StopAnimation() {
	GetPlayer()->StopAnimation();
}

int NCPlayer::GetClothes(lua_State* state) {
	LuaRef componentId = LuaRef::fromStack(state, 2);

	if (!componentId.isNumber() && componentId < 0 || componentId > 11) {
		return 0;
	}

	rage::clothData_t clothes = GetPlayer()->GetClothes((uint8_t)componentId);

	push(state, clothes.drawableId);
	push(state, clothes.textureId);
	push(state, clothes.paletteId);
	return 3;
}

void NCPlayer::SetClothes(uint8_t componentId, uint8_t drawable, uint8_t texture, uint8_t pelette) {
	if (componentId < 0 || componentId > 11) {
		return;
	}

	rage::clothData_t clothes = { drawable, texture, pelette };

	GetPlayer()->SetClothes(componentId, clothes);
	return;
}

int NCPlayer::GetProp(lua_State* state) {
	LuaRef propId = LuaRef::fromStack(state, 2);

	if (!propId.isNumber() && propId < 0 || propId > 3) {
		return 0;
	}

	rage::propData_t props = GetPlayer()->GetProp((uint8_t)propId);

	push(state, props.drawableId);
	push(state, props.textureId);
	return 2;
}

void NCPlayer::SetProp(uint8_t propId, uint8_t drawable, uint8_t texture) {
	if (propId < 0 || propId > 3) {
		return;
	}

	rage::propData_t props = { drawable, texture };

	GetPlayer()->SetProp(propId, props);
	return;
}

void NCPlayer::Eval(const std::string code) {
	GetPlayer()->Eval(code);
}

std::string NCPlayer::GetName() const {
	return GetPlayer()->GetName();
}

void NCPlayer::SetName(const std::string name) {
	GetPlayer()->SetName(name);
}

bool NCPlayer::IsAiming() const {
	return GetPlayer()->IsAiming();
}

bool NCPlayer::IsJumping() const {
	return GetPlayer()->IsJumping();
}

bool NCPlayer::IsInCover() const {
	return GetPlayer()->IsInCover();
}

bool NCPlayer::IsEnteringVehicle() const {
	return GetPlayer()->IsEnteringVehicle();
}

bool NCPlayer::IsLeavingVehicle() const {
	return GetPlayer()->IsLeavingVehicle();
}

bool NCPlayer::IsClimbing() const {
	return GetPlayer()->IsClimbing();
}

std::string NCPlayer::GetActionString() const {
	return GetPlayer()->GetActionString();
}

float NCPlayer::GetHeading() const {
	return GetPlayer()->GetHeading();
}

void NCPlayer::SetHeading(float heading) {
	GetPlayer()->SetHeading(heading);
}

float NCPlayer::GetMoveSpeed() const {
	return GetPlayer()->GetMoveSpeed();
}

float NCPlayer::GetHealth() const {
	return GetPlayer()->GetHealth();
}

void NCPlayer::SetHealth(float health) {
	GetPlayer()->SetHealth(health);
}

float NCPlayer::GetArmour() const {
	return GetPlayer()->GetArmour();
}

void NCPlayer::SetArmour(float armour) {
	GetPlayer()->SetArmour(armour);
}

NCVector3* NCPlayer::GetAimingAt() const {
	rage::vector3 vec = GetPlayer()->GetAimingAt();

	return new NCVector3(vec.x, vec.y, vec.z);
}

int NCPlayer::GetPing() const {
	return GetPlayer()->GetPing();
}

std::string NCPlayer::GetKickReason() const {
	return GetPlayer()->GetKickReason();
}

std::string NCPlayer::GetIp() const {
	return GetPlayer()->GetIp();
}

NCVehicle* NCPlayer::GetVehicleL() const {
	
	rage::IVehicle* vehicle = GetPlayer()->GetVehicle();

	if (vehicle) {
		NCVehicle* scriptVehicle = vehicle->External<NCVehicle>();
		return scriptVehicle;
	}

	return nullptr;
}

void NCPlayer::PutIntoVehicle(NCVehicle* vehicle, int8_t seatId) {
	if (!vehicle->GetVehicle()) {
		return;
	}

	GetPlayer()->PutIntoVehicle(vehicle->GetVehicle(), seatId);
}

void NCPlayer::RemoveFromVehicle() {
	GetPlayer()->RemoveFromVehicle();
}

uint8_t NCPlayer::GetSeat() const {
	return GetPlayer()->GetSeat();
}

uint8_t NCPlayer::GetEyeColour() const {
	return GetPlayer()->GetEyeColour();
}

void NCPlayer::SetEyeColour(uint8_t colour) {
	GetPlayer()->SetEyeColour(colour);
}

uint8_t NCPlayer::GetHairColour() const {
	return GetPlayer()->GetHairColour();
}

void NCPlayer::SetHairColourSecond(uint8_t colour) {
	GetPlayer()->SetHairColour(colour, GetPlayer()->GetHairHighlightColour());
}

uint8_t NCPlayer::GetHairHighlightColour() const {
	return GetPlayer()->GetHairHighlightColour();
}

void NCPlayer::SetHairHighlightColour(uint8_t colour) {
	GetPlayer()->SetHairColour(GetPlayer()->GetHairColour(), colour);
}

void NCPlayer::SetHairColour(uint8_t colour, uint8_t highlightColour) {
	GetPlayer()->SetHairColour(colour, highlightColour);
}

float NCPlayer::GetFaceFeature(uint8_t id) const {
	return GetPlayer()->GetFaceFeature(id);
}


void NCPlayer::SetFaceFeature(uint8_t id, float scale) {
	GetPlayer()->SetFaceFeature(id, scale);
}

int NCPlayer::GetHeadBlend(lua_State* state) {
	LuaRef table = LuaRef::newTable(state);

	rage::headBlend_t data = GetPlayer()->GetHeadBlend();

	table.append(data.m_shape[0]);
	table.append(data.m_shape[1]);
	table.append(data.m_shape[2]);
	table.append(data.m_skin[0]);
	table.append(data.m_skin[1]);
	table.append(data.m_skin[2]);
	table.append(data.m_shapeMix);
	table.append(data.m_skinMix);
	table.append(data.m_thirdMix);

	push(state, table);

	return 1;
}

int NCPlayer::SetHeadBlend(lua_State* state) {
	LuaRef shapeFirstID = LuaRef::fromStack(state, 2);
	LuaRef shapeSecondID = LuaRef::fromStack(state, 3);
	LuaRef shapeThirdID = LuaRef::fromStack(state, 4);
	LuaRef skinFirstID = LuaRef::fromStack(state, 5);
	LuaRef skinSecondID = LuaRef::fromStack(state, 6);
	LuaRef skinThirdID = LuaRef::fromStack(state, 7);
	LuaRef shapeMix = LuaRef::fromStack(state, 8);
	LuaRef skinMix = LuaRef::fromStack(state, 9);
	LuaRef thirdMix = LuaRef::fromStack(state, 10);

	if (!shapeFirstID.isNumber() ||
		!shapeSecondID.isNumber() ||
		!shapeThirdID.isNumber() ||
		!skinFirstID.isNumber() ||
		!skinSecondID.isNumber() ||
		!skinThirdID.isNumber() ||
		!shapeMix.isNumber() ||
		!skinMix.isNumber() ||
		!thirdMix.isNumber()
		) {
		return 0;
	}

	GetPlayer()->SetHeadBlend((int)shapeFirstID, (int)shapeSecondID, (int)shapeThirdID, (int)skinFirstID, (int)skinSecondID, (int)skinThirdID, (float)shapeMix, (float)skinMix, (float)thirdMix);
	return 0;
}

void NCPlayer::UpdateHeadBlend(float shapeMix, float skinMix, float thirdMix) {
	GetPlayer()->UpdateHeadBlend(shapeMix, skinMix, thirdMix);
}

uint32_t NCPlayer::GetWeapon() const {
	return GetPlayer()->GetWeapon();
}

int NCPlayer::GiveWeapon(lua_State* state) {
	LuaRef refModel = LuaRef::fromStack(state, 2);
	LuaRef refAmmo = LuaRef::fromStack(state, 3);

	if (!refAmmo.isNumber()) {
		return 0;
	}

	if (refModel.isNumber()) {

		GetPlayer()->GiveWeapon((uint32_t)refModel, (uint16_t)refAmmo);
	}
	else if (refModel.isString()) {
		GetPlayer()->GiveWeapon(Utility::joaat(refModel), (uint16_t)refAmmo);
	}

	return 0;
}

int NCPlayer::GiveWeapons(lua_State* state) {
	LuaRef table = LuaRef::fromStack(state, 2);
	std::vector<std::pair<rage::hash_t, uint16_t>> weapons;

	uint32_t value;

	if (!table.isTable()) {
		return 0;
	}

	for (Iterator iter(table); !iter.isNil(); ++iter)
	{
		LuaRef key = iter.key();
		LuaRef val = *iter;

		if (val.isTable()) {
			for (Iterator itera(val); !itera.isNil(); ++itera)
			{
				LuaRef keyW = itera.key();
				LuaRef valW = *itera;

				if (keyW == 1) {
					value = valW;
				}
				else if (keyW == 2) {
					weapons.push_back(std::make_pair((rage::hash_t)value, (uint32_t)valW));
					value = NULL;
				}
			}
		}
	}

	GetPlayer()->GiveWeapons(weapons);
	return 0;
}

std::string NCPlayer::GetSerial() const {
	return GetPlayer()->GetSerial();
}

int NCPlayer::Call(lua_State* state) {
	LuaRef eventName = LuaRef::fromStack(state, 2);

	if (!eventName.isString()) {
		return 0;
	}

	const int argsCountForFor = lua_gettop(state);
	const int argsCount = argsCountForFor - 2;

	rage::arg_t* arguments = new rage::arg_t[argsCount];

	for (int i = 3; i <= argsCountForFor; i++) {
		LuaRef argRef = LuaRef::fromStack(state, i);
		rage::arg_t arg;

		if (argRef.isNumber()) {
			double n = argRef;
			if (n == (int)n) {
				arg = (int)argRef;
			}
			else {
				arg = (float)argRef;
			}
		}
		else if (argRef.isBoolean()) {
			arg = (bool)argRef;
		}
		else if (argRef.isString()) {
			std::string str = argRef;
			arg = str;
		}

		arguments[i - 3] = arg;

	}

	GetPlayer()->_Call(eventName, arguments, argsCount);

	delete[] arguments;
	arguments = NULL;

	return 0;
}

int NCPlayer::Invoke(lua_State* state) {
	LuaRef eventName = LuaRef::fromStack(state, 2);

	if (!eventName.isString()) {
		return 0;
	}

	const int argsCountForFor = lua_gettop(state);
	const int argsCount = argsCountForFor - 2;

	rage::arg_t* arguments = new rage::arg_t[argsCount];

	for (int i = 3; i <= argsCountForFor; i++) {
		LuaRef argRef = LuaRef::fromStack(state, i);
		rage::arg_t arg;

		if (argRef.isNumber()) {
			double n = argRef;
			if (n == (int)n) {
				arg = (int)argRef;
			}
			else {
				arg = (float)argRef;
			}
		}
		else if (argRef.isBoolean()) {
			arg = (bool)argRef;
		}
		else if (argRef.isString()) {
			std::string str = argRef;
			arg = str;
		}

		arguments[i - 3] = arg;

	}

	GetPlayer()->_Invoke(eventName, arguments, argsCount);

	delete[] arguments;
	arguments = NULL;

	return 0;
}

bool NCPlayer::operator==(NCPlayer* player) const {
	return player->GetEntity() == GetEntity();
}

int NCPlayer::GetAtPlayer(lua_State* state) {
	LuaRef ref = LuaRef::fromStack(state, 1);

	if (!ref.isNumber()) {
		return 0;
	}

	rage::IPlayer* player = RaluCore::getInstance().getMultiPlayer()->GetPlayerPool().GetAt(ref);

	if (!player) {
		return 0;
	}

	NCPlayer* scriptPlayer = player->External<NCPlayer>();
	push(state, scriptPlayer);
	return 1;
}

int NCPlayer::Broadcast(lua_State* state) {
	LuaRef ref = LuaRef::fromStack(state, 1);

	if (!ref.isString()) {
		return 0;
	}

	RaluCore::getInstance().getMultiPlayer()->GetPlayerPool().Broadcast(Utility::toU16String(ref));
	return 0;
}

int NCPlayer::BroadcastInRange(lua_State* state) {
	LuaRef message = LuaRef::fromStack(state, 1);
	NCVector3* positionS = Userdata::get<NCVector3>(state, 2, false);
	LuaRef rangeS = LuaRef::fromStack(state, 3);
	LuaRef dimensionS = LuaRef::fromStack(state, 4);

	uint32_t dimension = 0;

	if (!message.isString() || !lua_isuserdata(state, 2) || !rangeS.isNumber()) {

		return 0;
	}

	rage::vector3 position = { positionS->coord[0], positionS->coord[1], positionS->coord[2] };

	if (dimensionS.isNumber()) {
		dimension = dimensionS;
	}

	RaluCore::getInstance().getMultiPlayer()->GetPlayerPool().BroadcastInRange(Utility::toU16String(message), position, (float)rangeS, dimension);
	return 0;
}

int NCPlayer::BroadcastInDimension(lua_State* state) {
	LuaRef message = LuaRef::fromStack(state, 1);
	LuaRef dimensionS = LuaRef::fromStack(state, 2);

	if (!message.isString() || !dimensionS.isNumber()) {
		return 0;
	}

	uint32_t dimension = dimensionS;
	RaluCore::getInstance().getMultiPlayer()->GetPlayerPool().BroadcastInDimension(Utility::toU16String(message), dimension);
	return 0;
}

bool NCPlayer::Exists(NCPlayer* player) {
	return player->entity ? true : false;
}

int NCPlayer::ForEach(lua_State* state) {
	LuaRef func = LuaRef::fromStack(state, 1);
	int size = 1;
	if (func.isFunction()) {
		for (rage::IPlayer* player : RaluCore::getInstance().getMultiPlayer()->GetPlayerPool()) {
			func(player->External<NCPlayer>(), size);
			size++;
		}
	}
	return 0;

}

int NCPlayer::ToArray(lua_State* state) {
	LuaRef table = LuaRef::newTable(state);

	for (rage::IPlayer* player : RaluCore::getInstance().getMultiPlayer()->GetPlayerPool()) {
		table.append(player->External<NCPlayer>());
	}

	push(state, table);
	return 1;
}

int NCPlayer::GetSize() {
	int size = 0;
	for (rage::IPlayer* player : RaluCore::getInstance().getMultiPlayer()->GetPlayerPool()) { size++; }
	return size;
}

void NCPlayer::Register(LuaVM* rVM) {
	getGlobalNamespace(rVM->GetVM())
	.beginClass<NCPlayer>("NCPlayer")
		.addFunction("__eq", &NCPlayer::operator==)
		.addProperty("id", &NCPlayer::GetId)
		.addProperty("type", &NCPlayer::GetType)
		.addProperty("dimension", &NCPlayer::GetDimension, &NCPlayer::SetDimension)
		.addProperty("position", &NCPlayer::GetPosition, &NCPlayer::SetPosition)
		.addProperty("rotation", &NCPlayer::GetRotation, &NCPlayer::SetRotation) // поворачивает всегда в одну сторону
		.addProperty("velocity", &NCPlayer::GetVelocity) // возвращает всего 0
		.addProperty("model", &NCPlayer::GetModel, &NCPlayer::SetModel)
		.addProperty("alpha", &NCPlayer::GetAlpha, &NCPlayer::SetAlpha)
		.addProperty("name", &NCPlayer::GetName, &NCPlayer::SetName)
		.addFunction("sendMessage", &NCPlayer::OutputChatBox)
		.addFunction("outputChatBox", &NCPlayer::OutputChatBox)
		.addFunction("notify", &NCPlayer::Notify)
		.addCFunction("spawn", &NCPlayer::Spawn)
		.addFunction("playAnimation", &NCPlayer::PlayAnimation)
		.addFunction("playScenario", &NCPlayer::PlayScenario)
		.addFunction("stopAnimation", &NCPlayer::StopAnimation)
		.addCFunction("getClothes", &NCPlayer::GetClothes)
		.addFunction("setClothes", &NCPlayer::SetClothes)
		.addCFunction("getProp", &NCPlayer::GetProp)
		.addFunction("setProp", &NCPlayer::SetProp)
		.addFunction("eval", &NCPlayer::Eval)
		.addProperty("isAiming", &NCPlayer::IsAiming)
		.addProperty("isJumping", &NCPlayer::IsJumping)
		.addProperty("isInCover", &NCPlayer::IsInCover)
		.addProperty("isEnteringVehicle", &NCPlayer::IsEnteringVehicle)
		.addProperty("isLeavingVehicle", &NCPlayer::IsLeavingVehicle)
		.addProperty("isClimbing", &NCPlayer::IsClimbing)
		.addProperty("action", &NCPlayer::GetActionString)
		.addProperty("heading", &NCPlayer::GetHeading, &NCPlayer::SetHeading)
		.addProperty("moveSpeed", &NCPlayer::GetMoveSpeed)
		.addProperty("health", &NCPlayer::GetHealth, &NCPlayer::SetHealth)
		.addProperty("armour", &NCPlayer::GetArmour, &NCPlayer::SetArmour)
		.addProperty("aimingAt", &NCPlayer::GetAimingAt)
		.addProperty("ping", &NCPlayer::GetPing)
		.addProperty("kickReason", &NCPlayer::GetKickReason)
		.addProperty("ip", &NCPlayer::GetIp)
		.addProperty("vehicle", &NCPlayer::GetVehicleL)
		.addFunction("putIntoVehicle", &NCPlayer::PutIntoVehicle)
		.addFunction("removeFromVehicle", &NCPlayer::RemoveFromVehicle)
		.addProperty("seat", &NCPlayer::GetSeat)
		.addProperty("eyeColour", &NCPlayer::GetEyeColour, &NCPlayer::SetEyeColour)
		.addProperty("hairColour", &NCPlayer::GetHairColour, &NCPlayer::SetHairColourSecond)
		.addProperty("hairHighlightColour", &NCPlayer::GetHairHighlightColour, &NCPlayer::SetHairHighlightColour)
		.addFunction("setHairColour", &NCPlayer::SetHairColour)
		.addFunction("setFaceFeature", &NCPlayer::SetFaceFeature)
		.addFunction("getFaceFeature", &NCPlayer::GetFaceFeature)
		.addCFunction("getHeadBlend", &NCPlayer::GetHeadBlend)
		.addCFunction("setHeadBlend", &NCPlayer::SetHeadBlend)
		.addFunction("updateHeadBlend", &NCPlayer::UpdateHeadBlend)
		.addProperty("weapon", &NCPlayer::GetWeapon)
		.addCFunction("giveWeapon", &NCPlayer::GiveWeapon)
		.addCFunction("giveWeapons", &NCPlayer::GiveWeapons)
		.addProperty("serial", &NCPlayer::GetSerial)
		.addCFunction("call", &NCPlayer::Call)
		.addCFunction("invoke", &NCPlayer::Invoke)
	.endClass()
	.beginNamespace("mp")
		.beginNamespace("players")
			.addCFunction("broadcast", &Broadcast)
			.addCFunction("broadcastInRange", &BroadcastInRange)
			.addCFunction("broadcastInDimension", &BroadcastInDimension)
			.addCFunction("at", &GetAtPlayer)
			.addFunction("exists", &Exists)
			.addCFunction("toArray", &ToArray)
			.addCFunction("forEach", &ForEach)
			.addFunction("size", &GetSize)
		.endNamespace()
	.endNamespace();
}