#pragma once
#include "Application/Event/InputEvent.h"
#include "Application/Event/WindowEvent.h"

class Layer  // NOLINT(cppcoreguidelines-special-member-functions)
{
public:
	virtual void OnInitialize(size_t screenWidth, size_t screenHeight) = 0;
	virtual void OnUpdate() = 0;

	virtual void OnEvent(InputEvent& inputEvent) {}
	virtual void OnEvent(WindowEvent& windowEvent) {}

	virtual void OnDestroy() = 0;

	virtual ~Layer() = default;
};

