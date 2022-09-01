#include "VertexArray.h"


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &arrayRef);
	Bind();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void VertexArray::Link(VertexBuffer& vbo, const GLuint layout)
{
	vbo.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(nullptr));
	glEnableVertexAttribArray(layout);
	vbo.Unbind();
}

void VertexArray::Bind() const
{
	glBindVertexArray(arrayRef);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &arrayRef);
}
