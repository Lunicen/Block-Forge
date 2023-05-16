#include "application/layer/sandbox/model/mesh/geometry/vertex_array.h"


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &_arrayRef);
	glBindVertexArray(_arrayRef);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void VertexArray::Link(const VertexBuffer& vbo, const GLuint layout, const GLint size, const GLsizei stride, const GLint offset) const
{
	vbo.Bind();

	glVertexAttribPointer(
		layout, size,
		GL_FLOAT, GL_FALSE,
		static_cast<GLsizei>(stride * sizeof(float)),
		reinterpret_cast<const void*>(offset * sizeof(float))  // NOLINT(performance-no-int-to-ptr)
	);
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
