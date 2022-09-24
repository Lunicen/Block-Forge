#pragma once
#include "Core/Log.h"
#include "Core/Metadata.h"
#include "ApplicationUtils.h"

class Application
{
	Log& _log = Log::Get();
	Metadata _settings;
	Window _window;

	void Initialize();

public:
	explicit Application(const std::string& filename);

	void Run();
};

