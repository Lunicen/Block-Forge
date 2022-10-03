#pragma once

class Layer  // NOLINT(cppcoreguidelines-special-member-functions)
{
public:
	virtual void OnUpdate() = 0;

	virtual void OnEvent() {}

	virtual ~Layer() = default;
};

