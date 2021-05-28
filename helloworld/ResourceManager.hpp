#pragma once
//#include <stdio.h>
#include "Resource.hpp"
#include <list>
#include "LuaVM.hpp"

class ResourceManager {
private:
	static ResourceManager* instance;
	std::string strResourceDirectory;

	std::list<Resource *> r_resources;

	typedef void(*CreateVM_t)(LuaVM*);
	CreateVM_t r_fnCreateVM = nullptr;
public:

	static ResourceManager* GetInstance() { return instance; }

	ResourceManager();
	ResourceManager(char* strResourceDirectory);
	~ResourceManager();

	void SetCreateVMCallback(CreateVM_t fnCreateVM) {
		r_fnCreateVM = fnCreateVM;
	}

	Resource* Load(std::string strAbsPath, std::string strResourceName);
	void UnLoad(Resource* resource);

	void pushResource(Resource* resource);
	void removeResource(Resource* resource);

	bool reloadResource(Resource* resource);
	bool startResource(Resource* resource);

	std::string getResourceDirectory() { return strResourceDirectory; }

	std::list<Resource*> GetResources() { return r_resources; }
	Resource* getResourceByName(std::string name);
	Resource* getResourceByVM(LuaVM* vm);
	Resource* getResourceByVM(lua_State* vm);
};