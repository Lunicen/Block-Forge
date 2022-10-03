#pragma once
#include "Application/Layer/PauseMenu/PauseMenuLayer.h"
#include "Application/Layer/Sandbox/SandboxLayer.h"
#include "Application/LayerStack/LayerStack.h"

/// @class SandboxStack
///	@brief Represents the stack responsible for the full simulation of the sandbox.
class SandboxStack final : public LayerStack
{
public:

	/// @brief The constructor.
	///	@param window - Reference to the window.
	explicit SandboxStack(Window& window)
	{
		Push(std::make_unique<SandboxLayer>(window));
		Push(std::make_unique<PauseMenuLayer>());
	}
};
