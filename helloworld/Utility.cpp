#include "Utility.hpp"

#ifdef _WIN32
#include <Windows.h>
#endif

#include <algorithm>
#include <memory>
#include <direct.h>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include "String.hpp"
#include <iostream>
#include <cuchar>
#include <vector>

namespace Utility
{

	std::string typeEntityToString(uint8_t type) {
		switch (type)
		{
		case 0: {
			return "player";
		}
		case 1: {
			return "vehicle";
		}
		case 2: {
			return "object";
		}
		case 3: {
			return "pickup";
		}
		case 4: {
			return "blip";
		}
		case 5: {
			return "checkpoint";
		}
		case 6: {
			return "marker";
		}
		case 7: {
			return "colshape";
		}
		default:
			return "unk";
		}
	}

	std::u16string toU16String(std::string text) {
		std::u16string wstr = u"";
		char16_t c16str[3] = u"\0";
		mbstate_t mbs;
		for (const auto& it : text) {
			memset(&mbs, 0, sizeof(mbs));
			memmove(c16str, u"\0\0\0", 3);
			mbrtoc16(c16str, &it, 3, &mbs);
			wstr.append(std::u16string(c16str));
		}
		return wstr;
	}

	std::string U16toString(std::u16string &wstr) {
		std::string str = "";
		char cstr[3] = "\0";
		mbstate_t mbs;
		for (const auto& it : wstr) {
			memset(&mbs, 0, sizeof(mbs));
			memmove(cstr, "\0\0\0", 3);
			c16rtomb(cstr, it, &mbs);
			str.append(std::string(cstr));
		}
		return str;
	}

	//stackoverflow
	std::string getcwd()
	{
		const size_t chunkSize = 255;
		const int maxChunks = 10240; // 2550 KiBs of current path are more than enough

		char stackBuffer[chunkSize]; // Stack buffer for the "normal" case
		if (_getcwd(stackBuffer, sizeof(stackBuffer)) != NULL)
			return stackBuffer;
		if (errno != ERANGE)
		{
			// It's not ERANGE, so we don't know how to handle it
			throw std::runtime_error("Cannot determine the current path.");
			// Of course you may choose a different error reporting method
		}
		// Ok, the stack buffer isn't long enough; fallback to heap allocation
		for (int chunks = 2; chunks<maxChunks; chunks++)
		{
			// With boost use scoped_ptr; in C++0x, use unique_ptr
			// If you want to be less C++ but more efficient you may want to use realloc
			std::auto_ptr<char> cwd(new char[chunkSize*chunks]);
			if (_getcwd(cwd.get(), chunkSize*chunks) != NULL)
				return cwd.get();
			if (errno != ERANGE)
			{
				// It's not ERANGE, so we don't know how to handle it
				throw std::runtime_error("Cannot determine the current path.");
				// Of course you may choose a different error reporting method
			}
		}
		throw std::runtime_error("Cannot determine the current path; the path is apparently unreasonably long");
	}

	std::string GetAbsolutePath(const char * szFormat, ...) {
		va_list args;
		char szBuffer[1024];
		va_start(args, szFormat);
		vsnprintf_s(szBuffer, sizeof(szBuffer), szFormat, args);
		va_end(args);
		return getcwd() + szBuffer;
	}

	
	uint32_t joaat(const char* str) {
		if (str) {
			size_t len = strlen(str);
			size_t i = 0;
			uint32_t hash = 0;
			while (i != len) {
				hash += (char)tolower(str[i++]);
				hash += hash << 10;
				hash ^= hash >> 6;
			}
			hash += hash << 3;
			hash ^= hash >> 11;
			hash += hash << 15;
			return hash;
		}

		return 0;
		
	}

	bool fileExist(const char * szPath) {
		struct stat St;
		return (stat(szPath, &St) == 0);
	}

	auto split(const std::string& value, char separator)
		-> std::vector<std::string>
	{
		std::vector<std::string> result;
		std::string::size_type p = 0;
		std::string::size_type q;
		while ((q = value.find(separator, p)) != std::string::npos) {
			result.emplace_back(value, p, q - p);
			p = q + 1;
		}
		result.emplace_back(value, p);
		return result;
	}

	/*long long GetTime() {
		return timeGetTime();
	}*/

}
