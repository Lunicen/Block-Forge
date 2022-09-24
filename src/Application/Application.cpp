#include "Application.h"

#include "Core/EngineExceptions.h"
#include "Sandbox/Sandbox.h"

void Application::Initialize()
{
	glfwInit();

	constexpr auto versionMajor = 3;
	constexpr auto versionMinor = 3;

	// The target version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const auto& width = static_cast<int>(_window.width);
	const auto& height = static_cast<int>(_window.height);

	_window.handle = glfwCreateWindow(width, height, "Block Forge", nullptr, nullptr);
	if (_window.handle == nullptr)
	{
		glfwTerminate();
		throw BadInitializationException("Failed to create window.");
	}

	glfwMakeContextCurrent(_window.handle);
	gladLoadGL();
	glViewport(0, 0, width, height);
}

Application::Application(const std::string& filename)
{
	_settings.Load(filename);
	_window.handle = nullptr;

	const auto resolution = _settings.GetJsonObject("resolution");
	_window.height = resolution["height"].get<int>();
	_window.width = resolution["width"].get<int>();
}

void Application::Run()
{
	Initialize();

	const auto sandbox = std::make_unique<Sandbox>(_window);
	sandbox->Run();

	_log.Info("Quitting...");

	glfwDestroyWindow(_window.handle);
	glfwTerminate();
}
