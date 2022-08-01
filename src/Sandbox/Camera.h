#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Utils/Shader.h"

class Camera
{
	Log& _log = Log::Get();

	glm::vec3 _position{};
	glm::vec3 _orientation{};
	glm::vec3 _up{};

	int _width, _height;
	float _speed, _sensitivity,
	      _fieldOfView, _nearPane, _farPane;

public:
	Camera(int width, int height, glm::vec3 position);

	void UpdateMatrix(const Shader& shader, const char* uniformName) const;

	int GetWidth() const;
	void SetWidth(int width);
	int GetHeight() const;
	void SetHeight(int height);
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
