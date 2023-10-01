#pragma once
#include "vertex_buffer.h"

/// @brief Vertex layout structure that represents its metadata.
struct VertexLayout
{
	/// @param Specifies the index of the attribute in the buffer.
	GLuint layout;
	
	/// @param Specifies the number of components per generic vertex attribute.
	/// @warning Must be 1, 2, 3 or 4.
	GLint size;

	/// @param Byte offset between consecutive generic vertex attributes.
	GLsizei stride;

	/// @param Offset of the first component of the first generic vertex attribute in the array.
	GLint offset;
};

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
	/// @param vbo - Vertex Buffer Object to which the VAO should be linked.\
	///	@param vertexLayout - Data format of the array of generic vertex attributes.
	void Link(const VertexBuffer& vbo, const VertexLayout& vertexLayout) const;

	/// @brief Tells OpenGL to bind the VAO.
	void Bind() const;

	/// @brief Tells OpenGL to unbind the VAO.
	void Unbind() const;

	~VertexArray();
};

