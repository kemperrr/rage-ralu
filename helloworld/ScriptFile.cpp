#include "ScriptFile.hpp"
#include <iostream>
//#include "ScriptArguments.hpp"
#include "Events.hpp"
ScriptFile::ScriptFile(Resource * resource, std::string szShortName, std::string szResourceFileName)
	: r_resource(resource),
	r_strResourceFileName(szResourceFileName),
	r_strShortName(szShortName)
{

}

ScriptFile::~ScriptFile()
{

}

bool ScriptFile::Start() {
	if (r_resource->getVM()->LoadScript(r_strShortName)) {
		ScriptArguments args;
		args.push(r_strResourceFileName);
		Events::GetInstance()->Call("scriptStarted", &args, EventHandler::rEventType::NATIVE_EVENT, 0, false);
		return true;
	}
	return false;
}

bool ScriptFile::Stop() {
	return true;
}