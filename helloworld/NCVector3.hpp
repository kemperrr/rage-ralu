#pragma once
#include "RaluCore.hpp"

class NCVector3 {
public:
	float coord[3];
	NCVector3(float x, float y, float z);

	std::string ToString() const;

	static void Register(LuaVM* rVM);
};

class NCVectorHelper {
public:
	template <unsigned index>
	static float get(NCVector3 const* vec)
	{
		return vec->coord[index];
	}

	template <unsigned index>
	static void set(NCVector3* vec, float value)
	{
		vec->coord[index] = value;
	}
};