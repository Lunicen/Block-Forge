#include "Application.h"

Application::Application(Metadata* configFile) : metadata(configFile)
{
	
}

void Application::Run()
{
	metadata->Load();

	while(true)
	{
		
	}
}
