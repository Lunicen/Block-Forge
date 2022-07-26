#include "ElementBuffer.h"

ElementBuffer::ElementBuffer(const GLuint* indices, const GLsizeiptr size)
{
	glGenBuffers(1, &ebo);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void ElementBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void ElementBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &ebo);
}
