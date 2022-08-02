#include "HumanInterfaceDevice.h"

HumanInterfaceDevice::HumanInterfaceDevice(GLFWwindow*& window) : _window(window)
{
}

bool HumanInterfaceDevice::IsKeyPressed(const KeyboardKey& key) const
{
	return glfwGetKey(_window, static_cast<int>(key)) == GLFW_PRESS;
}

bool HumanInterfaceDevice::IsKeyReleased(const KeyboardKey& key) const
{
	return glfwGetKey(_window, static_cast<int>(key)) == GLFW_RELEASE;
}

bool HumanInterfaceDevice::IsButtonPressed(const MouseButton& button) const
{
	return glfwGetMouseButton(_window, static_cast<int>(button)) == GLFW_PRESS;
}

bool HumanInterfaceDevice::IsButtonReleased(const MouseButton& button) const
{
	return glfwGetMouseButton(_window, static_cast<int>(button)) == GLFW_RELEASE;
}
