#pragma once
#include <vector>
#include "Structures.h"
#include <glad/glad.h>

/// @class VertexBuffer
/// @brief A Vertex Buffer Object handler - wrapper for the VBO functionality.
class VertexBuffer
{
	GLuint _bufferRef = 0;

public:

	/// @brief The constructor creates VBO, binds it immediately and sets its data.
	explicit VertexBuffer(const std::vector<Vertex>& vertices);

	explicit VertexBuffer(const std::vector<Matrix>& transformations);

	VertexBuffer(const VertexBuffer&) = delete;

	/// @brief Move constructor.
	VertexBuffer(VertexBuffer&&) = default;

	VertexBuffer& operator=(const VertexBuffer&) = delete;
	VertexBuffer& operator=(VertexBuffer&&) = default;

	/// @brief Tells OpenGL to bind the VBO.
	void Bind() const;

	/// @brief Tells OpenGL to unbind the VBO.
	void Unbind() const;

	~VertexBuffer();
};

