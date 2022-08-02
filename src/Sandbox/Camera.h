#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Utils/Shader.h"
#include "Events/HumanInterfaceDevice.h"

class Camera
{
	Log& _log = Log::Get();

	glm::vec3 _position{};
	glm::vec3 _orientation{};
	glm::vec3 _up{};

	int _width, _height;
	float _defaultSpeed, _speed, _sensitivity,
	      _fieldOfView, _nearPane, _farPane;

	HumanInterfaceDevice& _hid;
	GLFWwindow*& _window;
	bool _isPaused;

	void HandleHorizontalMovement(const KeyboardKey& left, const KeyboardKey& right, const KeyboardKey& forward, const KeyboardKey& backward);
	void HandleVerticalMovement(const KeyboardKey& up, const KeyboardKey& down);
	void HandleSpeed(const KeyboardKey& boost, float boostSpeed);
	void HandleCursorMovement();

public:
	Camera(GLFWwindow*& window, int width, int height, glm::vec3 position, HumanInterfaceDevice& hid);

	void UpdateMatrix(const Shader& shader, const char* uniformName) const;
	void HandleInput();

	int GetWidth() const;
	void SetWidth(int width);
	int GetHeight() const;
	void SetHeight(int height);
	float GetDefaultSpeed() const;
	void SetDefaultSpeed(float defaultSpeed);
	float GetSpeed() const;
	void SetSpeed(float speed);
	float GetSensitivity() const;
	void SetSensitivity(float sensitivity);
	float GetFieldOfView() const;
	void SetFieldOfView(float fieldOfView);
	float GetNearPane() const;
	void SetNearPane(float nearPane);
	float GetFarPane() const;
	void SetFarPane(float farPane);
};
