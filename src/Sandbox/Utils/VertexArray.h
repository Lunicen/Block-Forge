#pragma once
#include "VertexBuffer.h"

class VertexArray
{
	GLuint arrayRef = 0;

public:
	VertexArray();

	VertexArray(const VertexArray&) = delete;
	VertexArray(VertexArray&&) = delete;
	VertexArray& operator=(const VertexArray&) = delete;
	VertexArray& operator=(VertexArray&&) = delete;

	void Link(VertexBuffer& vbo, GLuint layout);
	void Bind() const;
	void Unbind();

	~VertexArray();
};

