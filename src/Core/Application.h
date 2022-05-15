#pragma once
#include "Metadata.h"

class Application
{
	Metadata* metadata;

public:
	Application() = delete;
	explicit Application(Metadata* configFile);

	void Run();
};

