#pragma once
#include <string>
#include "LuaVM.hpp"
#include "rage.hpp"
//#include "NCEntity.hpp"
#include "LuaBridge.h"
#include <iostream>

class NCEntity;
class LuaVM;

class ScriptArgument {
public:
	enum ArgumentType
	{
		ST_INVALID,
		ST_INTEGER,
		ST_BOOL,
		ST_FLOAT,
		ST_STRING,
		ST_ARRAY,
		ST_TABLE,
		ST_ENTITY,
		ST_REF,
	};
private:
	ArgumentType m_eType;
	rage::IEntity* entity;
	std::string str;
	int i;
	bool b;
	float f;
	luabridge::LuaRef* r;
public:

	ScriptArgument() { m_eType = ST_INVALID; }
	ScriptArgument(int ii) { m_eType = ST_INTEGER; i = ii; }
	ScriptArgument(bool bb) { m_eType = ST_BOOL; b = bb; }
	ScriptArgument(float ff) { m_eType = ST_FLOAT; f = ff; }
	ScriptArgument(const char* st) { m_eType = ST_STRING; str = st; }
	ScriptArgument(std::string strs) { m_eType = ST_STRING; str = strs; }
	ScriptArgument(rage::IEntity* entryEntity) { m_eType = ST_ENTITY; entity = entryEntity; }
	ScriptArgument(luabridge::LuaRef ref) { 
		m_eType = ST_REF; 
		r = &ref;
		std::cout << r->type() << " argument header" << std::endl;
	}
	//ScriptArgument(const ScriptArgument& p);
	~ScriptArgument();

	ArgumentType GetType() const { return m_eType; }

	void reset();

	void Push(LuaVM* pVM);

	void set(const ScriptArgument& p);

	void SetNull() { reset(); m_eType = ST_INVALID; }
	void SetInteger(int i) { reset(); m_eType = ST_INTEGER; i = i; }
	void SetBool(bool b) { reset(); m_eType = ST_BOOL; b = b; }
	void SetFloat(float f) { reset(); m_eType = ST_FLOAT; f = f; }
	void SetString(const char s) { reset(); m_eType = ST_STRING; str = s; }
	void SetString(std::string s) { reset(); m_eType = ST_STRING; str = s; }
	void SetEntity(rage::IEntity* entryEntity) { reset(); m_eType = ST_ENTITY; entity = entryEntity; }
	void SetRef(luabridge::LuaRef* ref) { reset(); m_eType = ST_REF; r = *ref; }


	int				GetInteger() const { return (m_eType == ST_INTEGER) ? i : 0; }
	bool			GetBool() const { return (m_eType == ST_BOOL) ? b : false; }
	float			GetFloat() const { return (m_eType == ST_FLOAT) ? f : 0.0f; }
	const char *	GetString() const { return (m_eType == ST_STRING) ? str.c_str() : NULL; }
	luabridge::LuaRef* GetRef() const { return (m_eType == ST_REF) ? r : NULL; }

	bool pushFromStack(LuaVM * pVM, int idx);
};