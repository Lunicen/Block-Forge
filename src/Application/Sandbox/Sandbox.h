#pragma once
#include "Core/Log.h"
#include "Application/Window.h"

/// @class Sandbox
/// @brief Class where the world is projected.
///	@details This class handles displaying the world or so to say the actual simulation.
class Sandbox
{
	Log& _log = Log::Get();
	Window& _window;

public:

	/// @brief The constructor.
	///	@param window - Reference to the window settings.
	explicit Sandbox(Window& window);

	/// @brief Initializes the simulation.
	void Run() const;
};

