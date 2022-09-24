#include "Core/Log.h"
#include "Application/Application.h"

int main(const int argc, char *argv[])
{
	const auto& log = Log::Get();
	const auto configFile = argc > 1 ? argv[1] : "Settings.json";

	try
	{
		const auto application = new Application(configFile);
		application->Run();
	}
	catch (std::exception& e)
	{
		log.Critical(e.what());
		return 1;
	}

	return 0;
}
