#include "json.hpp"
#include "RaluCore.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>
#include "LuaBridge\LuaBridge.h"
#include <locale> 
#include <codecvt> 
#include "Events.hpp"
//#include <cuchar>
//#include <ctime>
//#include <vector>

#include "NCALL.hpp"
#include "NCEvents.hpp"

#ifdef _WIN32
#include <Windows.h>
#endif

using namespace luabridge;
using json = nlohmann::json;

void onCreateVM(LuaVM* rVM)
{
	NCEvents::Register(rVM);
	NCVector3::Register(rVM);
	NCCheckpoint::Register(rVM);
	NCPlayer::Register(rVM);
	NCVehicle::Register(rVM);
	NCBlip::Register(rVM);
	NCMarker::Register(rVM);
	NCColshape::Register(rVM);
	NCObject::Register(rVM);
	NCTimer::Register(rVM);
	NCCommand::Register(rVM);
	getGlobalNamespace(rVM->GetVM())
		.beginNamespace("mp")
			.addFunction("joaat", &Utility::joaat)
		.endNamespace();
}

bool RaluCore::initialize(rage::IMultiplayer *mp) {

	this->mp = mp;

	if (!this->initializeEventHandlers()) {
		return false;
	}

	std::string configFileName = Utility::GetAbsolutePath("/conf.json").c_str();

	if (!Utility::fileExist(configFileName.c_str())) {
		return false;
	}

	std::ifstream configFile;
	configFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	json JSONConfig;

	try {
		std::cout << "\033[1;32m[Ralu]\033[0m Read config file";
		configFile.open(configFileName);
		configFile >> JSONConfig;
		std::cout << " -\033[1;32m Success\033[0m" << std::endl;
	}
	catch (const std::ifstream::failure& e) {
		std::cout << " -\033[1;31m Error read\033[0m" << std::endl;
		std::cout << e.what() << std::endl;
		return false;
	}
	
	configFile.close();

	Events * events = new Events();
	
	instanceTimerManager = new TimerManager();

	instanceCommandManager = new CommandManager();

	instanceResourceManager = new ResourceManager(RESOURCE_DIRECTORY);
	instanceResourceManager->SetCreateVMCallback(onCreateVM);
	std::cout << "\033[1;32m[Ralu]\033[0m [=================== Loading Resources ===================]\n" << std::endl;

	int countResourceSucces = 0;
	int countResourceFailed = 0;

	for (std::string element : JSONConfig["resources"]) {
		if (element.size() != 0) {
			std::cout << "\033[1;32m[Ralu]\033[0m Load resource " << element;
			if (Resource * resource = instanceResourceManager->Load(Utility::GetAbsolutePath(instanceResourceManager->getResourceDirectory().c_str()), element.c_str())) {
				if (!instanceResourceManager->startResource(resource)) {
					countResourceFailed++;
				}
				else
				{
					countResourceSucces++;
				}
			}
			else 
			{
				countResourceFailed++;
			}
		}
	}

	events->Call("resourcesStarted", NULL, EventHandler::rEventType::NATIVE_EVENT, 0, false);

	std::cout << "\n\033[1;32m[Ralu]\033[0m " << countResourceSucces << " resources successfully loaded ( " << countResourceFailed << " failed )"<< std::endl;
	std::cout << "\033[1;32m[Ralu]\033[0m [=========================================================]" << std::endl;

	return true;
}

bool RaluCore::initializeEventHandlers() {

	mp->AddEventHandler(new PlayerEvents);
	mp->AddEventHandler(new VehicleEvents);
	mp->AddEventHandler(new EntityEvents);
	mp->AddEventHandler(new ColshapeEvents);
	mp->AddEventHandler(new TickEvents);
	mp->AddEventHandler(new CheckpointEvents);

	return true;
}