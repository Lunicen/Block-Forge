#include "HumanInterfaceDevice.h"

HumanInterfaceDevice::HumanInterfaceDevice(Window& window) : _window(window)
{
}

std::pair<double, double> HumanInterfaceDevice::GetCursorPosition() const
{
	double x;
	double y;
	glfwGetCursorPos(_window.GetHandle(), &x, &y);

	return {x, y};
}

void HumanInterfaceDevice::SetCursorPosition(const double x, const double y) const
{
	glfwSetCursorPos(_window.GetHandle(), x, y);
}

void HumanInterfaceDevice::EnableCursor() const
{
	glfwSetInputMode(_window.GetHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void HumanInterfaceDevice::DisableCursor() const
{
	glfwSetInputMode(_window.GetHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
