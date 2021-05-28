#include "ScriptArguments.hpp"
#include <iostream>

ScriptArguments::~ScriptArguments()
{
	reset();
}

ScriptArguments::ScriptArguments()
{
	reset();
}

ScriptArguments::ScriptArguments(const ScriptArguments& p) {
	for (auto argument : p.m_Arguments) {
		m_Arguments.push_back(new ScriptArgument(*argument));
	}
}

void ScriptArguments::reset()
{
	for (auto argument : m_Arguments) {
		delete argument;
	}

	m_Arguments.clear();
}

void ScriptArguments::push(int i)
{
	m_Arguments.push_back(new ScriptArgument(i));
}

void ScriptArguments::push(bool b)
{
	m_Arguments.push_back(new ScriptArgument(b));
}

void ScriptArguments::push(float f)
{
	m_Arguments.push_back(new ScriptArgument(f));
}

void ScriptArguments::push(const char* c)
{
	m_Arguments.push_back(new ScriptArgument(c));
}

void ScriptArguments::push(std::string str)
{
	m_Arguments.push_back(new ScriptArgument(str));
}

void ScriptArguments::push(rage::IEntity* entryEntity) 
{
	m_Arguments.push_back(new ScriptArgument(entryEntity));
}

void ScriptArguments::push(luabridge::LuaRef ref) {
	//std::cout << (*ref).isTable() << std::endl;
	std::cout << ref.type() << " arguments " << std::endl;
	//luabridge::LuaRef proxyRef = (*ref);
	m_Arguments.push_back(new ScriptArgument(ref));
}

/*void ScriptArguments::push(const ScriptArguments &array, bool isArray)
{
	m_Arguments.push_back(new ScriptArgument(array, isArray));
}*/

/*void ScriptArguments::push(ScriptArguments* pArray, bool isArray)
{
	m_Arguments.push_back(new ScriptArgument(*pArray, isArray));
}*/