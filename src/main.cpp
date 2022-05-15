#include "Core/Application.h"
#include "Core/Log.h"

int main()
{
	Log::Init();
	auto appConfig = std::make_unique<Metadata>("src/Data/Config.json");

	Application application(appConfig);
	application.Run();

	return 0;
}
