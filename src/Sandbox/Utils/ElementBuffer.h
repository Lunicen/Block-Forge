#pragma once
#include <glad/glad.h>

/// @class ElementBuffer
/// @brief A Vertex Array Object handler - wrapper for the VAO functionality.
class ElementBuffer
{
	GLuint ebo = 0;

public:

	/// @brief The constructor creates EBO, binds it immediately and sets its data.
	explicit ElementBuffer(const GLuint* indices, GLsizeiptr size);

	ElementBuffer(const ElementBuffer& buffer) = delete;
	ElementBuffer(ElementBuffer&& buffer) = delete;
	ElementBuffer& operator=(const ElementBuffer& buffer) = delete;
	ElementBuffer& operator=(ElementBuffer&& buffer) = delete;

	/// @brief Tells OpenGL to bind the EBO.
	void Bind() const;

	/// @brief Tells OpenGL to unbind the EBO.
	void Unbind();

	~ElementBuffer();
};

