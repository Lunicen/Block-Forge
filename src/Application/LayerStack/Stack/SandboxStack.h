#pragma once
#include "Application/Layer/Sandbox/SandboxLayer.h"
#include "Application/LayerStack/LayerStack.h"

class SandboxStack final : public LayerStack
{
public:
	SandboxStack(size_t windowWidth, size_t windowHeight)
	{
		Push(std::make_unique<SandboxLayer>(windowWidth, windowHeight));
	}
};
