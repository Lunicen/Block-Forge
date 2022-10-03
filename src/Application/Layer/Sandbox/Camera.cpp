#include "Camera.h"

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

	if (!_isPaused)
	{
		UpdateCursorMovement();
	}
}

void Camera::HandleHorizontalMovement()
{
	if (_hid.IsPressed(_left))
	{
		_position += _speed * -normalize(cross(_orientation, _upVector));
	}
	if (_hid.IsPressed(_right))
	{
		_position += _speed * normalize(cross(_orientation, _upVector));
	}
	if (_hid.IsPressed(_forward))
	{
		_position += _speed * _orientation;
	}
	if (_hid.IsPressed(_backward))
	{
		_position += _speed * -_orientation;
	}
}

void Camera::HandleVerticalMovement()
{
	if (_hid.IsPressed(_up))
	{
		_position += _speed * _upVector;
	}
	if (_hid.IsPressed(_down))
	{
		_position += _speed * -_upVector;
	}
}

void Camera::HandleSpeed(const float boostSpeed)
{
	_speed = _hid.IsPressed(_boost) ? boostSpeed : _defaultSpeed;
}

void Camera::UpdateCursorMovement()
{
	const auto& mousePosition = _hid.GetCursorPosition();
	const auto& mouseX = mousePosition.first;
	const auto& mouseY = mousePosition.second;

	const auto& middleAxisX = mouseX / 2.0;
	const auto& middleAxisY = mouseY / 2.0;

	const float xAxisRotation = _sensitivity * (static_cast<float>(middleAxisY) / static_cast<float>(_window.GetHeight()));
	const float yAxisRotation = _sensitivity * (static_cast<float>(middleAxisX) / static_cast<float>(_window.GetWidth()));

	const auto orientation = rotate(_orientation, glm::radians(-xAxisRotation), normalize(cross(_orientation, _upVector)));
	const auto angleWithXAxis = abs(angle(orientation, _upVector) - glm::radians(90.0f));

	// This prevents the barrel roll situation when looking up
	if (angleWithXAxis < glm::radians(85.0f))
	{
		_orientation = orientation;
	}

	_orientation = rotate(_orientation, glm::radians(-yAxisRotation), _upVector);

	_hid.SetCursorPosition(middleAxisX, middleAxisY);
}

Camera::Camera(Window& window, glm::vec3 position, HumanInterfaceDevice& hid)
	: _hid(hid),
	  _window(window),
	  _position(position)
{
	_hid.DisableCursor();
}

void Camera::Bind(Shader const& shader) const
{
	shader.Load();
	glUniformMatrix4fv(glGetUniformLocation(shader.GetProgram(), "camera"), 1, GL_FALSE, value_ptr(_orthographicProjection));
}

void Camera::HandleInput()
{
	if (_hid.IsPressedOnce(KeyboardKey::escape))
	{
		_isPaused = !_isPaused;
		_isPaused ? _hid.EnableCursor() : _hid.DisableCursor();
	}

	if (_isPaused)
	{
		return;
	}

	HandleHorizontalMovement();
	HandleVerticalMovement();
	HandleSpeed(0.4f);
}

glm::vec3 Camera::GetPosition() const
{
	return _position;	
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