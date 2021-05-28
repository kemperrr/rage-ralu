#pragma once
#include <string>
#include "Resource.hpp"
class Resource;

class ScriptFile {

private:
	Resource * r_resource;
	std::string r_strResourceFileName;
	std::string r_strShortName;
public:
	ScriptFile(Resource * resource, std::string szShortName, std::string szResourceFileName);
	~ScriptFile();

	bool	Start();
	bool	Stop();
};
