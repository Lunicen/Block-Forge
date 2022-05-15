#pragma once
#include "Metadata.h"

class Application
{
	std::unique_ptr<Metadata> metadata;

public:
	Application() = delete;
	explicit Application(std::unique_ptr<Metadata>& configFile);

	void Run();
};

