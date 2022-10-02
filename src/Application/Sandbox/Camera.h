#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Model/Mesh/Geometry/Shader.h"
#include "Application/Event/InputEvent.h"
#include "Application/HID/KeyCodes.h"

/// @class Camera
/// @brief Handles input to allow spectating the world.
///	@details This class handles HID interface data which events interprets in order to move around the loaded world.
class Camera
{
	Log& _log = Log::Get();

	size_t _screenHeight;
	size_t _screenWidth;

	glm::vec3 _position{};
	glm::vec3 _orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 _upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 _orthographicProjection = glm::mat4(1.0f);

	float _defaultSpeed = 0.1f;
	float _speed = 0.1f;
	float _sensitivity = 100.0f;
	float _fieldOfView = 45.0f;
	float _nearPane = 0.1f;
	float _farPane = 100.0f;

	bool _isPaused = false;

	const KeyboardKey _left = KeyboardKey::a;
	const KeyboardKey _right = KeyboardKey::d;
	const KeyboardKey _forward = KeyboardKey::w;
	const KeyboardKey _backward = KeyboardKey::s;

	const KeyboardKey _up = KeyboardKey::space;
	const KeyboardKey _down = KeyboardKey::leftCtrl;

	const KeyboardKey _boost = KeyboardKey::leftShift;

	void HandleHorizontalMovement(InputEvent& input);
	void HandleVerticalMovement(InputEvent& input);
	void HandleSpeed(float boostSpeed, InputEvent& input);
	void UpdateCursorMovement(InputEvent& input);

public:
	/// @brief The constructor.
	/// @param position - Spawn point of the camera.
	Camera(size_t screenWidth, size_t screenHeight, glm::vec3 position);

	/// @brief Update the camera orthogonal projection settings.
	void Update();

	/// @brief Binds the camera handling to the shader.
	///	@param shader - shader to bind the camera matrix.
	void Bind(Shader const& shader) const;

	/// @brief Captures input and moves the camera accordingly.
	void HandleInput(InputEvent& input);

	/// @brief Get camera position.
	///	@return Returns 3D vector representation.
	glm::vec3 GetPosition() const;

	/// @brief Get default speed.
	///	@details The default speed is the normal speed of the camera.
	float GetDefaultSpeed() const;

	/// @brief Set default speed.
	///	@param defaultSpeed - camera default speed value.
	void SetDefaultSpeed(float defaultSpeed);

	/// @brief Get current camera speed.
	float GetSpeed() const;

	/// @brief Set current camera speed.
	///	@param speed - speed value.
	void SetSpeed(float speed);

	/// @brief Get camera sensitivity.
	float GetSensitivity() const;

	/// @brief Set camera sensitivity.
	///	@note Applies to the devices that are manipulating the cursor.
	void SetSensitivity(float sensitivity);

	/// @brief Get field of view.
	float GetFieldOfView() const;

	/// @brief Set field of view.
	///	@param fieldOfView - FOV value.
	void SetFieldOfView(float fieldOfView);

	/// @brief Get near pane.
	float GetNearPane() const;

	/// @brief Set near pane.
	///	@param nearPane - the **shortest** distance that allows to render the object in front of the camera.
	void SetNearPane(float nearPane);

	/// @brief Get far pane.
	float GetFarPane() const;

	/// @brief Set far pane.
	///	@param farPane - the **longest** distance that allows to render the object in front of the camera.
	void SetFarPane(float farPane);
};
