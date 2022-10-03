#pragma once
#include "Application/Layer/PauseMenu/PauseMenuLayer.h"
#include "Application/Layer/Sandbox/SandboxLayer.h"
#include "Application/LayerStack/LayerStack.h"

class SandboxStack final : public LayerStack
{
public:
	SandboxStack(Window& window, HumanInterfaceDevice& hid)
	{
		Push(std::make_unique<SandboxLayer>(window, hid));
		Push(std::make_unique<PauseMenuLayer>(hid));
	}
};
