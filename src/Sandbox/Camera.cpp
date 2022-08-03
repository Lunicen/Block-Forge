#include "Camera.h"

Camera::Camera(GLFWwindow*& window, const int width, const int height, const glm::vec3 position, HumanInterfaceDevice& hid) : _position(position), _width(width), _height(height), _hid(hid), _window(window)
{
	if (width <= 0 || height <= 0)
	{
		_log.Warn(
			"The width and height of a window must be a positive number. Given: width = " + std::to_string(width) +
			"height = " + std::to_string(height));
	}

	_orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	_up = glm::vec3(0.0f, 1.0f, 0.0f);

	_speed = 0.1f;
	_defaultSpeed = _speed;
	_sensitivity = 100.0f;

	_fieldOfView = 45.0f;
	_nearPane = 0.1f;
	_farPane = 100.0f;

	_isPaused = false;

	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Camera::HandleHorizontalMovement(const KeyboardKey& left, const KeyboardKey& right, const KeyboardKey& forward,
	const KeyboardKey& backward)
{
	if (_hid.IsPressed(left))
	{
		_position += _speed * -normalize(cross(_orientation, _up));
	}
	if (_hid.IsPressed(right))
	{
		_position += _speed * normalize(cross(_orientation, _up));
	}
	if (_hid.IsPressed(forward))
	{
		_position += _speed * _orientation;
	}
	if (_hid.IsPressed(backward))
	{
		_position += _speed * -_orientation;
	}
}

void Camera::HandleVerticalMovement(const KeyboardKey& up, const KeyboardKey& down)
{
	if (_hid.IsPressed(up))
	{
		_position += _speed * _up;
	}
	if (_hid.IsPressed(down))
	{
		_position += _speed * -_up;
	}
}

void Camera::HandleSpeed(const KeyboardKey& boost, const float boostSpeed)
{
	_speed = _hid.IsPressed(boost) ? boostSpeed : _defaultSpeed;
}

void Camera::HandleCursorMovement()
{
	double mouseX;
	double mouseY;
	glfwGetCursorPos(_window, &mouseX, &mouseY);

	const double middleAxisX = static_cast<double>(_width) / 2.0;
	const double middleAxisY = static_cast<double>(_height) / 2.0;
	const float xAxisRotation = _sensitivity * (static_cast<float>(mouseY - middleAxisY) / static_cast<float>(_height));
	const float yAxisRotation = _sensitivity * (static_cast<float>(mouseX - middleAxisX) / static_cast<float>(_width));

	const auto orientation = rotate(_orientation, glm::radians(-xAxisRotation), normalize(cross(_orientation, _up)));
	const auto angleWithXAxis = abs(angle(orientation, _up) - glm::radians(90.0f));

	// This prevents the barrel roll situation when looking up
	if (angleWithXAxis < glm::radians(88.0f))
	{
		_orientation = orientation;
	}

	_orientation = rotate(_orientation, glm::radians(-yAxisRotation), _up);
	glfwSetCursorPos(_window, middleAxisX, middleAxisY);
}

void Camera::AddToShader(const Shader& shader, const char* uniformName) const
{
	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	auto view = glm::mat4(1.0f);
	view = lookAt(_position, _position + _orientation, _up);

	const float aspectRatio = static_cast<float>(_width) / static_cast<float>(_height);

	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	auto projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(_fieldOfView), aspectRatio, _nearPane, _farPane);

	glUniformMatrix4fv(glGetUniformLocation(shader.GetProgram(), uniformName), 1, GL_FALSE, value_ptr(projection * view));
}

void Camera::HandleInput()
{
	if (_hid.IsPressedOnce(KeyboardKey::escape))
	{
		_isPaused = !_isPaused;
		if (_isPaused)
		{
			glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else
		{
			glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}
	}

	if (_isPaused)
	{
		return;
	}

	HandleHorizontalMovement(KeyboardKey::a, KeyboardKey::d, KeyboardKey::w, KeyboardKey::s);
	HandleVerticalMovement(KeyboardKey::space, KeyboardKey::leftShift);
	HandleSpeed(KeyboardKey::leftCtrl, 0.4f);
	HandleCursorMovement();
}

inline int Camera::GetWidth() const
{
	return _width;
}

inline void Camera::SetWidth(const int width)
{
	_width = width;
}

inline int Camera::GetHeight() const
{
	return _height;
}

inline void Camera::SetHeight(const int height)
{
	_height = height;
}

inline float Camera::GetDefaultSpeed() const
{
	return _defaultSpeed;
}

inline void Camera::SetDefaultSpeed(const float defaultSpeed)
{
	_defaultSpeed = defaultSpeed;
}

inline float Camera::GetSpeed() const
{
	return _speed;
}

inline void Camera::SetSpeed(const float speed)
{
	_speed = speed;
}

inline float Camera::GetSensitivity() const
{
	return _sensitivity;
}

inline void Camera::SetSensitivity(const float sensitivity)
{
	_sensitivity = sensitivity;
}

inline float Camera::GetFieldOfView() const
{
	return _fieldOfView;
}

inline void Camera::SetFieldOfView(const float fieldOfView)
{
	_fieldOfView = fieldOfView;
}

inline float Camera::GetNearPane() const
{
	return _nearPane;
}

inline void Camera::SetNearPane(const float nearPane)
{
	_nearPane = nearPane;
}

inline float Camera::GetFarPane() const
{
	return _farPane;
}

inline void Camera::SetFarPane(const float farPane)
{
	_farPane = farPane;
}