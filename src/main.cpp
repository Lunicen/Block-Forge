#include "Core/Application.h"

int main()
{
	auto appConfig = std::make_unique<Metadata>("src/Core/Config.json");

	Application application(std::move(appConfig));
	application.Run();

	return 0;
}