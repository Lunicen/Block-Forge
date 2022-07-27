#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const GLfloat* vertices, const GLsizeiptr size)
{
	glGenBuffers(1, &bufferRef);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferRef);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &bufferRef);
}
