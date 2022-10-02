#include "Camera.h"

Camera::Camera(Window& window, const glm::vec3 position) : _window(window), _position(position)
{
	glfwSetInputMode(_window.GetHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Camera::Update()
{
	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	auto view = glm::mat4(1.0f);
	view = lookAt(_position, _position + _orientation, _upVector);

	const float aspectRatio = static_cast<float>(_window.GetWidth()) / static_cast<float>(_window.GetHeight());

	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	auto projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(_fieldOfView), aspectRatio, _nearPane, _farPane);

	_orthographicProjection = projection * view;
}

void Camera::HandleHorizontalMovement(InputEvent& input)
{
	if (input.IsPressed(_left))
	{
		_position += _speed * -normalize(cross(_orientation, _upVector));
	}
	if (input.IsPressed(_right))
	{
		_position += _speed * normalize(cross(_orientation, _upVector));
	}
	if (input.IsPressed(_forward))
	{
		_position += _speed * _orientation;
	}
	if (input.IsPressed(_backward))
	{
		_position += _speed * -_orientation;
	}
}

void Camera::HandleVerticalMovement(InputEvent& input)
{
	if (input.IsPressed(_up))
	{
		_position += _speed * _upVector;
	}
	if (input.IsPressed(_down))
	{
		_position += _speed * -_upVector;
	}
}

void Camera::HandleSpeed(const float boostSpeed, InputEvent& input)
{
	_speed = input.IsPressed(_boost) ? boostSpeed : _defaultSpeed;
}

void Camera::UpdateCursorMovement()
{
	double mouseX;
	double mouseY;
	glfwGetCursorPos(_window.GetHandle(), &mouseX, &mouseY);

	const double middleAxisX = static_cast<double>(_window.GetWidth()) / 2.0;
	const double middleAxisY = static_cast<double>(_window.GetHeight()) / 2.0;

	const float xAxisRotation = _sensitivity * (static_cast<float>(mouseY - middleAxisY) / static_cast<float>(_window.GetHeight()));
	const float yAxisRotation = _sensitivity * (static_cast<float>(mouseX - middleAxisX) / static_cast<float>(_window.GetWidth()));

	const auto orientation = rotate(_orientation, glm::radians(-xAxisRotation), normalize(cross(_orientation, _upVector)));
	const auto angleWithXAxis = abs(angle(orientation, _upVector) - glm::radians(90.0f));

	// This prevents the barrel roll situation when looking up
	if (angleWithXAxis < glm::radians(85.0f))
	{
		_orientation = orientation;
	}

	_orientation = rotate(_orientation, glm::radians(-yAxisRotation), _upVector);
	glfwSetCursorPos(_window.GetHandle(), middleAxisX, middleAxisY);
}

void Camera::Bind(Shader const& shader) const
{
	shader.Load();
	glUniformMatrix4fv(glGetUniformLocation(shader.GetProgram(), "camera"), 1, GL_FALSE, value_ptr(_orthographicProjection));
}

void Camera::HandleInput(InputEvent& input)
{
	if (input.IsPressedOnce(KeyboardKey::escape))
	{
		_isPaused = !_isPaused;
		if (_isPaused)
		{
			glfwSetInputMode(_window.GetHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else
		{
			glfwSetInputMode(_window.GetHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}

	if (_isPaused)
	{
		return;
	}

	HandleHorizontalMovement(input);
	HandleVerticalMovement(input);
	HandleSpeed(0.4f, input);
	UpdateCursorMovement();
}

glm::vec3 Camera::GetPosition() const
{
	return _position;	
}

inline size_t Camera::GetWidth() const
{
	return _window.GetWidth();
}

inline size_t Camera::GetHeight() const
{
	return _window.GetHeight();
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