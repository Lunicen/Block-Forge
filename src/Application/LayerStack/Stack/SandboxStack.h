#pragma once
#include "Application/Layer/Sandbox/SandboxLayer.h"
#include "Application/LayerStack/LayerStack.h"

class SandboxStack final : public LayerStack
{
public:
	SandboxStack(Window& window, HumanInterfaceDevice& hid) : LayerStack(hid.GetEventListener())
	{
		Push(std::make_unique<SandboxLayer>(window, hid));
	}
};
