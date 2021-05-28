#pragma once

#include "RaluCore.hpp"
#include "NCEntity.hpp"
#include "NCVehicle.hpp"

class NCVehicle;

class NCPlayer : public NCEntity {
public:
	NCPlayer(rage::IEntity* entryEntity);

	void Kick(const char *reason);
	void Ban(const char *reason);
	void OutputChatBox(const std::string text);
	void Notify(const std::string text);
	int Spawn(lua_State* state);
	void PlayAnimation(std::string dict, std::string name, float speed, int flags);
	void PlayScenario(const std::string scenario);
	void StopAnimation();
	int GetClothes(lua_State* state);
	void SetClothes(uint8_t componentId, uint8_t drawable, uint8_t texture, uint8_t pelette);
	int GetProp(lua_State* state);
	void SetProp(uint8_t propId, uint8_t drawable, uint8_t texture);
	void Eval(const std::string code);
	std::string GetName() const;
	void SetName(const std::string name);
	bool IsAiming() const;
	bool IsJumping() const;
	bool IsInCover() const;
	bool IsEnteringVehicle() const;
	bool IsLeavingVehicle() const;
	bool IsClimbing() const;
	std::string GetActionString() const;
	float GetHeading() const;
	void SetHeading(float heading);
	float GetMoveSpeed() const;
	float GetHealth() const;
	void SetHealth(float health);
	float GetArmour() const;
	void SetArmour(float armour);
	NCVector3* GetAimingAt() const;
	int GetPing() const;
	std::string GetKickReason() const;
	std::string GetIp() const;
	NCVehicle* GetVehicleL() const; // TODO NCVehicle
	void PutIntoVehicle(NCVehicle* vehicle, int8_t seatId); // TODO NCVehicle
	void RemoveFromVehicle();
	uint8_t GetSeat() const;
	uint8_t GetEyeColour() const;
	void SetEyeColour(uint8_t colour);
	uint8_t GetHairColour() const;
	void SetHairColourSecond(uint8_t colour);
	uint8_t GetHairHighlightColour() const;
	void SetHairHighlightColour(uint8_t colour);
	void SetHairColour(uint8_t colour, uint8_t highlightColour);
	float GetFaceFeature(uint8_t id) const;
	void SetFaceFeature(uint8_t id, float scale);
	int GetHeadBlend(lua_State* state);
	int SetHeadBlend(lua_State* state);
	void UpdateHeadBlend(float shapeMix, float skinMix, float thirdMix);
	uint32_t GetWeapon() const;
	int GiveWeapon(lua_State* state);
	int GiveWeapons(lua_State* state);
	std::string GetSerial() const;
	int Call(lua_State* state);
	int Invoke(lua_State* state);
	bool operator==(NCPlayer* player) const;

	static void Register(LuaVM* rVM);
private:
	static bool Exists(NCPlayer* player);
	static int GetAtPlayer(lua_State* state);
	static int Broadcast(lua_State* state);
	static int BroadcastInRange(lua_State* state);
	static int BroadcastInDimension(lua_State* state);
	static int ForEach(lua_State* state);
	static int ToArray(lua_State* state);
	static int GetSize();
};
