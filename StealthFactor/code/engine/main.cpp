#include <iostream>
#include <cli.hpp>
#include <engine/Engine.hpp>

#if defined(PLATFORM_LINUX)
#include <unistd.h>

#elif defined(PLATFORM_WINDOWS)
#include <windows.h>

#else
#error Unsupported platform
#endif

int main(int argc, const char **argv)
{
	cli::Parser parser(argc, argv);

	parser.help()
		<< R"(Stealth Factor)";

	auto dataPath = parser.option("data")
		.description("Path to data directory")
		.defaultValue("data")
		.getValue();

#if defined(PLATFORM_LINUX)
	if (chdir(dataPath))
	{
		std::cerr << "Unable to set data directory." << std::endl;
		return EXIT_FAILURE;
	}

#elif defined(PLATFORM_WINDOWS)
	wchar_t wDataPath[4096];
	MultiByteToWideChar(CP_ACP, 0, dataPath, -1, wDataPath, 4096);
	if (!SetCurrentDirectory(wDataPath))
	{
		std::cerr << "Unable to set data directory." << std::endl;
		return EXIT_FAILURE;
	}
#endif

	engine::Engine::getInstance().loadConfiguration();
	engine::Engine::getInstance().run();

	return EXIT_SUCCESS;
}


// NEEDED for Friday 10:
// - Clear Layer and dependencies cleaning + make a class diagram of the refactored code
// - Actor / Component need to be implemented
// - Remove singleton
// - Implement ownership using smrt pointr (especially unique) and RIAA

// Remove THAT MUCH dependencies in the managers or at least explicit it ("class SGSGDFGDF" in the hpp)
// DECOUPLE : Use components, Inheritance or Interface ?  Or observer like Strategy or Observer
// Reimplement actor / component pattern
// REMOVE Singleton : use pointers or observer pattern
// Avoid Macros (the main one)? Use premake or something with a class that deal with setting data and to separate linus and windows folder?
// Have coherent code style
// For the physic manager shit, use a void* or template (or contexpr) to pass collision shit
// Graphic manager should become a manager. 
// Create some struct for the caharcter data or idk ?
// Do some abstraction to be able to change library or whatever in the future 


// diff between a pointer and a reference : 
// 1. A reference cannot be null
// 2. A pointer use arrow and a reference use a point.
// 3. You cannot change the adress linked to a refe  rence