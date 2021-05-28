#pragma once
#include <list>
#include "ScriptArgument.hpp"
#include "rage.hpp"
#include "LuaBridge.h"

class ScriptArgument;

class ScriptArguments {

public:
	ScriptArguments();
	ScriptArguments(const ScriptArguments& p);
	~ScriptArguments();

	void reset();

	void push(int i);
	void push(bool b);
	void push(float f);
	void push(const char* c);
	void push(std::string str);
	void push(rage::IEntity* entryEntity);
	void push(luabridge::LuaRef ref);
	//void push(const ScriptArgument &arg);
	//void push(const ScriptArguments &array, bool isArray);
	//void push(ScriptArguments* pArray, bool isArray);
	
	//ScriptArgument pop();
	std::list<ScriptArgument *> m_Arguments;
};