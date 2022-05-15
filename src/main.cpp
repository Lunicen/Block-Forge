#include "Core/Application.h"

int main()
{
	auto appConfig = std::make_unique<Metadata>("src/Core/Config.json");

	Application application(appConfig);
	application.Run();

	return 0;
}