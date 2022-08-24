#include "VertexArray.h"


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &_arrayRef);
	Bind();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void VertexArray::Link(const VertexBuffer& vbo, const GLuint layout) const
{
	vbo.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(nullptr));
	glEnableVertexAttribArray(layout);
	vbo.Unbind();
}

void VertexArray::Bind() const
{
	glBindVertexArray(_arrayRef);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &_arrayRef);
}
