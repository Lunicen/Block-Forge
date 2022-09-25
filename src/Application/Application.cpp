#include "Application.h"

#include "Core/EngineExceptions.h"
#include "Sandbox/Sandbox.h"

// As a static member of class this variable
// must be here initialized
Window Application::_window = {
	nullptr, 0, 0
};

void Application::WindowResizeEvent(GLFWwindow*, const int width, const int height)
{
	glViewport(0, 0, width, height);

	_window.width = static_cast<size_t>(width);
	_window.height = static_cast<size_t>(width);
}

void Application::CentralizeWindow() const
{
	const auto& x = _fullscreenWidth / 2 - _window.width / 2;
	const auto& y = _fullscreenHeight / 2 - _window.height / 2;

	glfwSetWindowPos(_window.handle, static_cast<int>(x), static_cast<int>(y));
}

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

	glfwSetWindowUserPointer(_window.handle, this);

	glViewport(0, 0, width, height);

	const auto screenMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	_fullscreenWidth = screenMode->width;
	_fullscreenHeight = screenMode->height;

	if (_fullscreenWidth < static_cast<size_t>(width) || _fullscreenHeight < static_cast<size_t>(height))
	{
		_log.Warn("The resolution size settings " + 
			std::to_string(width) + "x" + std::to_string(height) + 
			" exceed the supported monitor resolution " + 
			std::to_string(_fullscreenWidth) + "x" + std::to_string(_fullscreenHeight) +
			"."
		);
	}

	glfwSetFramebufferSizeCallback(_window.handle, WindowResizeEvent);

	CentralizeWindow();

	_log.Info("Block Forge initialized!");
}

Application::Application(const std::string& filename)
{
	_settings.Load(filename);

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
