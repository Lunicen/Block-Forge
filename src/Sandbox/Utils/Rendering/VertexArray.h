#pragma once
#include "VertexBuffer.h"

/// @class VertexArray
/// @brief A Vertex Array Object handler - wrapper for the VAO functionality.
class VertexArray
{
	GLuint _arrayRef = 0;

public:

	/// @brief The constructor creates VAO and binds it immediately.
	VertexArray();

	VertexArray(const VertexArray&) = delete;
	VertexArray(VertexArray&&) = delete;
	VertexArray& operator=(const VertexArray&) = delete;
	VertexArray& operator=(VertexArray&&) = delete;

	/// @brief Links the VAO to the VBO.
	///	@param vbo - Vertex Buffer Object to which the VAO should be linked.
	///	@param layout - index of the attribute in the buffer.
	///	@param size - number of components 
	///	@param stride - byte offset between consecutive generic vertex attributes.
	///	@param offset - offset of the first component of the first generic vertex attribute in the array.
	void Link(const VertexBuffer& vbo, const GLuint layout, const GLint size, const GLsizei stride, GLint offset) const;

	/// @brief Tells OpenGL to bind the VAO.
	void Bind() const;

	/// @brief Tells OpenGL to unbind the VAO.
	void Unbind() const;

	~VertexArray();
};

