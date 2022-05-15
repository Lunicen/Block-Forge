#include "Core/Application.h"

int main()
{
	auto appConfig = std::make_unique<VoxelLobster::Metadata>("src/Core/Config.json");

	VoxelLobster::Application application(appConfig);
	application.Run();

	return 0;
}