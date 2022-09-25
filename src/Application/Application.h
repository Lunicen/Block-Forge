#pragma once
#include "Core/Log.h"
#include "Core/Metadata.h"
#include "ApplicationUtils.h"

class Application
{
	static Window _window;

	Log& _log = Log::Get();
	Metadata _settings;

	size_t _fullscreenWidth{};
	size_t _fullscreenHeight{};

	static void WindowResizeEvent(GLFWwindow*, int width, int height);
	void CentralizeWindow() const;
	void Initialize();

public:
	explicit Application(const std::string& filename);

	void Run();
};

