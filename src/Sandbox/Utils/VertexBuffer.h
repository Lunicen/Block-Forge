#pragma once
#include <glad/glad.h>

class VertexBuffer
{
	GLuint bufferRef = 0;

public:
	explicit VertexBuffer(const GLfloat* vertices, GLsizeiptr size);

	VertexBuffer(const VertexBuffer&) = delete;
	VertexBuffer(VertexBuffer&&) = delete;
	VertexBuffer& operator=(const VertexBuffer&) = delete;
	VertexBuffer& operator=(VertexBuffer&&) = delete;

	void Bind() const;
	void Unbind();

	~VertexBuffer();
};

