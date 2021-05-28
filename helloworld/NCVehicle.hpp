#pragma once

#include "RaluCore.hpp"
#include "NCEntity.hpp"
#include "NCPlayer.hpp"

class NCPlayer;

class NCVehicle : public NCEntity {
public:
	NCVehicle(rage::IEntity* entryEntity);

	void Destroy();
	bool IsSirenActive() const;
	void SetSirenActive(bool toggle);
	bool IsHornActive() const;
	bool AreHighbeamsActive() const;
	void SetHighbeamsActive(bool toggle);
	bool AreLightsActive() const;
	void SetLightsActive(bool toggle);
	bool IsEngineActive() const;
	void SetEngineActive(bool toggle);
	bool IsRocketBoostActive() const;
	bool IsBrakeActive() const;
	float GetSteerAngle() const;
	float GetGasPedalState() const;
	float GetEngineHealth() const;
	float GetBodyHealth() const;
	NCPlayer* GetOccupant(uint8_t seat) const;
	int GetOccupants(lua_State* state);
	void SetOccupant(uint8_t seat, NCPlayer* player);
	bool IsLocked() const;
	void Lock(bool toggle);
	bool IsDead() const;
	void Explode();
	void Spawn(NCVector3* pos, float heading);
	uint8_t GetMod(uint8_t id) const;
	void SetMod(uint8_t id, uint8_t mod);
	bool AreNeonsEnabled() const;
	void EnableNeons(bool toggle);
	void SetNeonsColour(uint8_t r, uint8_t g, uint8_t b);
	int GetNeonsColour(lua_State* state);
	void Repair();
	int GetColourRGB(lua_State* state);
	uint8_t GetColour(uint8_t id) const;
	uint8_t GetPaint(uint8_t id) const;
	void SetColourRGB(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2);
	void SetColour(uint8_t primary, uint8_t secondary);
	void SetPaint(uint8_t type1, uint8_t colour1, uint8_t type2, uint8_t colour2);
	uint8_t GetMaterialType() const;
	std::string GetNumberPlate() const;
	void SetNumberPlate(const std::string numberPlate);
	bool operator==(NCVehicle* vehicle) const;

	static void Register(LuaVM* rVM);
private:
	static int CreateVehicle(lua_State* state);
	static int GetAtVehicle(lua_State* state);
	static bool Exists(NCVehicle* vehicle);
	static int ForEach(lua_State* state);
	static int ToArray(lua_State* state);
	static int GetSize();
};