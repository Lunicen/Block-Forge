#pragma once
#include <vector>
#include "Structures.h"
#include <glad/glad.h>

/// @class ElementBuffer
/// @brief A Vertex Array Object handler - wrapper for the VAO functionality.
class ElementBuffer
{
	GLuint _bufferRef = 0;

public:

	/// @brief The constructor creates EBO, binds it immediately and sets its data.
	explicit ElementBuffer(const std::vector<TriangleIndexes>& indices);

	ElementBuffer(const ElementBuffer& buffer) = delete;

	/// @brief Move constructor.
	ElementBuffer(ElementBuffer&& buffer) = default;

	ElementBuffer& operator=(const ElementBuffer& buffer) = delete;

	/// @brief Move assignment constructor.
	ElementBuffer& operator=(ElementBuffer&& buffer) = default;

	/// @brief Tells OpenGL to bind the EBO.
	void Bind() const;

	/// @brief Tells OpenGL to unbind the EBO.
	void Unbind() const;

	~ElementBuffer();
};

