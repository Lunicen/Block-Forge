#pragma once
#include "Application/Event/Event.h"

class Layer  // NOLINT(cppcoreguidelines-special-member-functions)
{
public:
	virtual void Initialize() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnEvent(Event& eventToHandle) = 0;
	virtual void Destroy() = 0;

	virtual ~Layer() = default;
};

