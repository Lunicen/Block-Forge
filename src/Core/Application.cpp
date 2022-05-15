#include "Application.h"

namespace VoxelLobster
{
	Application::Application(std::unique_ptr<Metadata>& configFile) : metadata(std::move(configFile))
	{
		
	}

	void Application::Run()
	{
		metadata->Load();

		while(true)
		{
			
		}
	}
}

