#pragma once
#include "ScriptFile.hpp"
#include <list>
#include "LuaVM.hpp"

class ScriptFile;
class LuaVM;

class Resource {
private:
	std::string strAbsPath;
	std::string strResourceName;
	std::string strResourceDirectoryPath;

	std::list<ScriptFile *>	r_resourceFiles;

	bool r_Loaded;
	bool r_Active;

	LuaVM* r_VM;

	typedef void(*CreateVM_t)(LuaVM*);
	CreateVM_t r_fnCreateVM = nullptr;
	
public:
	Resource();
	Resource(std::string strAbsPath, std::string strResourceName);
	~Resource();
	
	bool load();
	bool unload();
	bool reload();
	bool start();
	bool stop();

	bool IsLoaded() { return r_Loaded; }
	bool IsActive() { return r_Active; }

	bool createVM();
	void destroyVM();

	LuaVM* getVM() { return r_VM; };

	std::string getName() { return strResourceName; }

	void setCreateVMCallback(CreateVM_t fnCreateVM) {
		r_fnCreateVM = fnCreateVM;
	}
};