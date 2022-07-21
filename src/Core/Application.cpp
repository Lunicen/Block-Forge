#include "Application.h"
#include "Sandbox/Sandbox.h"

Application::Application(std::unique_ptr<Metadata>& configFile) : metadata(std::move(configFile))
{
	
}

void Application::Run()
{
	metadata->Load();

	auto sandbox = new Sandbox("test.json");
	sandbox->Run();
}
