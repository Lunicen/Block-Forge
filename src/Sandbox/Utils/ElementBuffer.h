#pragma once
#include <glad/glad.h>

class ElementBuffer
{
public:
	GLuint ebo = 0;
	explicit ElementBuffer(const GLuint* indices, GLsizeiptr size);

	ElementBuffer(const ElementBuffer& buffer) = delete;
	ElementBuffer(ElementBuffer&& buffer) = delete;
	ElementBuffer& operator=(const ElementBuffer& buffer) = delete;
	ElementBuffer& operator=(ElementBuffer&& buffer) = delete;

	void Bind() const;
	void Unbind();

	~ElementBuffer();
};

