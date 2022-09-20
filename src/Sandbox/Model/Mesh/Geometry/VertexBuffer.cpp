#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const std::vector<Vertex>& vertices)
{
	const auto verticesSize = 
		static_cast<GLsizeiptr>(vertices.size()) * 
		static_cast<GLsizeiptr>(sizeof(Vertex));

	glGenBuffers(1, &_bufferRef);
	glBindBuffer(GL_ARRAY_BUFFER, _bufferRef);
	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices.data(), GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(const std::vector<Matrix>& transformations)
{
	const auto matricesSize = 
		static_cast<GLsizeiptr>(transformations.size()) * 
		static_cast<GLsizeiptr>(sizeof(Matrix));

	glGenBuffers(1, &_bufferRef);
	glBindBuffer(GL_ARRAY_BUFFER, _bufferRef);
	glBufferData(GL_ARRAY_BUFFER, matricesSize, transformations.data(), GL_STATIC_DRAW);
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
