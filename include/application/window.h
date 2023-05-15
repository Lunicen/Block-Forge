#pragma once
#include "Core/opengl_headers.h"

/// @class Window
///	@brief This is a container for holding the data concerning the application window.
///	@note This parameters of the instance of this class should be modified **only** by the @see Application.
class Window
{
	GLFWwindow* _handle = nullptr;
	size_t _width = 0;
	size_t _height = 0;

public:

	/// @brief Returns a reference to the window context.
	GLFWwindow* GetHandle() const
	{
		return _handle;
	}

	/// @brief Returns the width of the window.
	size_t GetWidth() const
	{
		return _width;
	}

	/// @brief Returns the height of the window.
	size_t GetHeight() const
	{
		return _height;
	}

	/// @brief Sets a handle to the window context.
	void SetHandle(GLFWwindow* handle)
	{
		_handle = handle;
	}

	/// @brief Sets the width of the window.
	void SetWidth(const size_t width)
	{
		_width = width;
	}

	/// @brief Sets the height of the window.
	void SetHeight(const size_t height)
	{
		_height = height;
	}
};