#pragma once
#include "Application/Event/InputEvent.h"
#include "Application/Event/WindowEvent.h"

class Layer  // NOLINT(cppcoreguidelines-special-member-functions)
{
public:
	virtual void OnUpdate() = 0;

	virtual void OnEvent(InputEvent& inputEvent) {}
	virtual void OnEvent(WindowEvent& windowEvent) {}

	virtual ~Layer() = default;
};

