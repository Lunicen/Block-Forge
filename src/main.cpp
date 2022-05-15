#include "Core/Application.h"

int main()
{
	auto appConfig = Metadata("src/Data/Config.json");
	appConfig.Load();

	Application application(&appConfig);
	application.Run();

	return 0;
}