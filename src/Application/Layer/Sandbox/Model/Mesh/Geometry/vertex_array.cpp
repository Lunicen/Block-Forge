#include "application/layer/sandbox/model/mesh/geometry/vertex_array.h"


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &_arrayRef);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void VertexArray::Link(const VertexBuffer& vbo, const VertexLayout& vertexLayout) const
{
	vbo.Bind();

	glVertexAttribPointer(
		vertexLayout.layout, vertexLayout.size,
		GL_FLOAT, GL_FALSE,
		static_cast<GLsizei>(vertexLayout.stride * sizeof(float)),
		reinterpret_cast<const void*>(vertexLayout.offset * sizeof(float))  // NOLINT(performance-no-int-to-ptr)
	);
	glEnableVertexAttribArray(vertexLayout.layout);

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
