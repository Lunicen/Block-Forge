#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const std::vector<Vertex>& vertices)
{
	const auto verticesDataSize = static_cast<GLsizeiptr>(vertices.size()) * static_cast<GLsizeiptr>(sizeof(Vertex));

	glGenBuffers(1, &_bufferRef);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, verticesDataSize, vertices.data(), GL_STATIC_DRAW);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, _bufferRef);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &_bufferRef);
}
