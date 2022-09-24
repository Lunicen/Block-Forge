#pragma once
#include "Core/Log.h"
#include "Core/Metadata.h"
#include "ApplicationUtils.h"

class Application
{
	Log& _log = Log::Get();
	Metadata _settings;
	Window _window{};

	size_t _fullscreenWidth{};
	size_t _fullscreenHeight{};

	void CentralizeWindow() const;
	void Initialize();

public:
	explicit Application(const std::string& filename);

	void Run();
};

