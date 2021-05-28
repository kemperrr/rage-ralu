#pragma once
#include <string>
#include <vector>

namespace Utility
{
	std::string GetAbsolutePath(const char * szFormat, ...);
	std::string getcwd();
	uint32_t joaat(const char* str);
	bool fileExist(const char * szPath);
	std::u16string toU16String(std::string text);
	std::string U16toString(std::u16string &wstr);
	std::string typeEntityToString(uint8_t type);
	std::vector<std::string> split(const std::string& value, char separator);
	//long long GetTime();
};