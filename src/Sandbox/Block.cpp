#include "Block.h"

#include <glm/gtx/transform.hpp>


Block::Block(float x, float y, float z) //there must be initialization list otherwise memory will be used more, and also because reference demands initialization lits
{
	this->x = x;
	this->y = y;
	this->z = z;

	VertexBuffer vbo(vertices, sizeof(vertices));
	ElementBuffer ebo(indices, sizeof(indices));

	vao.Link(vbo, 0);

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	Move(x, y, z);
}

void Block::Move(float x, float y, float z)
{
	const auto origin = glm::mat4(1.0f);
	const auto moveTo = glm::vec3(x, y, z);

	translate(origin, moveTo);
}

void Block::Draw()
{
	vao.Bind();
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, nullptr);
}
