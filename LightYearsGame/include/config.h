#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG //Release Build
	return "assets/";

#else
	return "C:/Dev/LightYears/LightYearsGame/assets/";

#endif
}
