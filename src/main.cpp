#include "Core/Application.h"
#include "Core/Log.h"
#include "Core/MainMenu.h"

int main()
{
	Log& instance = Log::Get();

	auto appConfig = std::make_unique<Metadata>("src/Data/Config.json");


	MainMenu mainMenu = MainMenu();
	mainMenu.Draw();


	Application application(appConfig);
	application.Run();

	return 0;
}
