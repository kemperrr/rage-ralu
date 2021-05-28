#ifdef WIN32
#include <Windows.h>
#endif
#include <iostream>
#include <codecvt> 
#include <string>
#include "rage.hpp"
#include "RaluCore.hpp"

RAGE_API rage::IPlugin *InitializePlugin(rage::IMultiplayer *mp)
{	
	/*SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RUS");*/

	std::cout << "\033[1;32m[Ralu]\033[0m Initialize ... " << std::endl;

	if (!RaluCore::getInstance().initialize(mp)) {
		std::cout << "\033[1;31m[Ralu]\033[0m Initialize failure... " << std::endl;
		exit(EXIT_FAILURE);
		return nullptr;
	}

	std::cout << "\033[1;32m[Ralu]\033[0m Initialize complete" << std::endl;

	return new rage::IPlugin;
}
