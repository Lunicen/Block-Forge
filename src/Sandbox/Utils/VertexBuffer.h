#pragma once
#include <glad/glad.h>

/// @class VertexBuffer
/// @brief A Vertex Buffer Object handler - wrapper for the VBO functionality.
class VertexBuffer
{
	GLuint _bufferRef = 0;

public:

	/// @brief The constructor creates VBO, binds it immediately and sets its data.
	explicit VertexBuffer(const GLfloat* vertices, GLsizeiptr size);

	VertexBuffer(const VertexBuffer&) = delete;

	/// @brief Move constructor.
	VertexBuffer(VertexBuffer&&) = default;

	VertexBuffer& operator=(const VertexBuffer&) = delete;
	VertexBuffer& operator=(VertexBuffer&&) = delete;

	/// @brief Tells OpenGL to bind the VBO.
	void Bind() const;

	/// @brief Tells OpenGL to unbind the VBO.
	void Unbind();

	~VertexBuffer();
};

