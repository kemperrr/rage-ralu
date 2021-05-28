#include "ResourceManager.hpp"
#include <iostream>
#include <assert.h>

ResourceManager* ResourceManager::instance = NULL;

ResourceManager::ResourceManager() : strResourceDirectory("resources/")
{
	instance = this;
}

ResourceManager::ResourceManager(char* strResourceDirectory) : strResourceDirectory(strResourceDirectory)
{
	instance = this;
}

ResourceManager::~ResourceManager() {
	
}

void ResourceManager::pushResource(Resource* resource) {
	assert(std::find(r_resources.begin(), r_resources.end(), resource) == r_resources.end());
	
	r_resources.push_back(resource);
}

void ResourceManager::removeResource(Resource* resource) {
	assert(std::find(r_resources.begin(), r_resources.end(), resource) != r_resources.end());

	r_resources.remove(resource);
}

bool ResourceManager::reloadResource(Resource* resource) {
	resource->reload();

	if (!resource->IsLoaded()) {
		return false;
	}
	return true;
}

bool ResourceManager::startResource(Resource* resource) {
	if (!resource->IsActive()) {
		if (resource->start()) {
			return true;
		}
	}
	resource->stop();
	return false;
}

Resource* ResourceManager::Load(std::string strAbsPath, std::string strResourceName) {
	
	Resource* resource = new Resource(strAbsPath, strResourceName);
	if (!resource->IsLoaded()) {
		std::cout << " - \033[1;31m[ERROR]\033[0m" << std::endl;
		delete resource;
		resource = NULL;
	} else {
		std::cout << " - \033[1;32m[SUCCESS]\033[0m" << std::endl;
		resource->setCreateVMCallback(r_fnCreateVM);
		pushResource(resource);
		return resource;
	}
	return 0;
}

void ResourceManager::UnLoad(Resource* resource) {
	resource->stop();
	removeResource(resource);
	delete resource;
	return;
}

Resource* ResourceManager::getResourceByName(std::string name) {
	for (auto resource : r_resources)
	{
		if (resource->getName() == name)
			return resource;
	}

	return nullptr;
}

Resource* ResourceManager::getResourceByVM(LuaVM* vm) {
	for (auto resource : r_resources)
	{
		if (resource->getVM() == vm)
			return resource;
	}

	return nullptr;
}

Resource* ResourceManager::getResourceByVM(lua_State* vm) {
	for (auto resource : r_resources)
	{
		if (resource->getVM()->GetVM() == vm)
			return resource;
	}

	return nullptr;
}