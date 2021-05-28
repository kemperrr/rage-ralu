#include "Resource.hpp"
#include "json.hpp"
#include <fstream>
#include "Events.hpp"

using json = nlohmann::json;

Resource::Resource() 
	: r_VM(0),
	strAbsPath(""),
	strResourceName(""), 
	r_Loaded(false),
	r_Active(false)
{
}

Resource::Resource(std::string sstrAbsPath, std::string sstrResourceName)
	: r_VM(0),
	strAbsPath(sstrAbsPath),
	strResourceName(sstrResourceName),
	r_Loaded(false),
	r_Active(false)
{
	strResourceDirectoryPath = strAbsPath + "/" + strResourceName;
	load();
}

Resource::~Resource() {

}

bool Resource::load() {
	std::string strMetaFile = strResourceDirectoryPath + "/" + "meta.json";

	std::ifstream configFile;
	configFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	json JSONConfig;

	try {
		configFile.open(strMetaFile);
		configFile >> JSONConfig;
	}
	catch (const std::ifstream::failure& e) {
		std::cout << " \n" << e.what() << std::endl;
		return false;
	}

	configFile.close();

	if (JSONConfig["server"].size() == 0) {
		return false;
	}

	for (std::string element : JSONConfig["server"]) {
		std::string scriptFile = strResourceDirectoryPath;
		r_resourceFiles.push_back(new ScriptFile(this, scriptFile + "/" + element, element));
	}

	r_Loaded = true;
	return true;
}

bool Resource::start() {
	if (IsLoaded()) {
		createVM();
		for (auto scriptFile : r_resourceFiles)
		{
			if (!scriptFile->Start())
			{
				destroyVM();
				r_Active = false;
				return false;
			}

		}
		r_Active = true;

		ScriptArguments args;
		args.push(strResourceName);
		Events::GetInstance()->Call("resourceStarted", &args, EventHandler::rEventType::NATIVE_EVENT, r_VM, false);
		return true;
	}
	return false;
}

bool Resource::stop() {
	if (IsLoaded())
	{
		for (auto scriptFile : r_resourceFiles)
		{
			delete scriptFile;
		}
		r_resourceFiles.clear();
		destroyVM();
	}

	r_Active = false;

	return true;
}

bool Resource::unload() {
	stop();
	r_Loaded = false;
	return true;
}

bool Resource::reload() {
	unload();
	load();
	return true;
}

bool Resource::createVM() {
	if (IsLoaded() && !r_VM) {
		r_VM = new LuaVM(this);

		if (r_fnCreateVM) {
			r_fnCreateVM(r_VM);
		}
		return true;
	}

	return false;
}

void Resource::destroyVM() {
	if (!r_VM)
		return;

	r_VM = nullptr;
	return;
}