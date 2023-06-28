#pragma once
#include "application/layer/pause_menu/pause_menu_layer.h"
#include "application/layer/sandbox/sandbox_layer.h"
#include "application/layer_stack/layer_stack.h"

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
