#include "HID.h"

HID::HID(Window& window) : _window(window)
{
}

std::pair<double, double> HID::GetCursorPosition() const
{
	double x;
	double y;
	glfwGetCursorPos(_window.GetHandle(), &x, &y);

	return {x, y};
}

void HID::SetCursorPosition(const double x, const double y) const
{
	glfwSetCursorPos(_window.GetHandle(), x, y);
}

void HID::EnableCursor() const
{
	glfwSetInputMode(_window.GetHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void HID::DisableCursor() const
{
	glfwSetInputMode(_window.GetHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
