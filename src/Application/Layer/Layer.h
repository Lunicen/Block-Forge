#pragma once
#include "Application/Event/KeyboardEvent.h"
#include "Application/Event/MouseEvent.h"
#include "Application/Event/WindowEvent.h"

class Layer  // NOLINT(cppcoreguidelines-special-member-functions)
{
public:
	virtual void OnUpdate() = 0;

	virtual void OnEvent(KeyboardEvent& inputEvent) {}
	virtual void OnEvent(MouseEvent& windowEvent) {}
	virtual void OnEvent(WindowEvent& windowEvent) {}

	virtual ~Layer() = default;
};

