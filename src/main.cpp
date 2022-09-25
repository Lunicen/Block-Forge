#include "Core/Log.h"
#include "Application/Application.h"

void ParseArguments(char *argumentsArray[], const int argumentsCount)
{
	for (auto i = 1; i < argumentsCount; ++i)
	{
		if (strcmp(argumentsArray[i], "--trace") == 0)
		{
			Log::SetMode(Log::LogMode::trace);
		}

		if (strcmp(argumentsArray[i], "--debug") == 0)
		{
			Log::SetMode(Log::LogMode::debug);
		}
	}
}

int main(const int argc, char *argv[])
{
	const auto& log = Log::Get();
	ParseArguments(argv, argc);

	try
	{
		const auto application = new Application("Settings.json");
		application->Run();
	}
	catch (std::exception& e)
	{
		log.Critical(e.what());
		return 1;
	}

	return 0;
}
