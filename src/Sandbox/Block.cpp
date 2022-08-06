#include "Block.h"



Block::Block(float x, float y, float z, Shader &shader) : shader(shader) //there must be initialization list otherwise memory will be used more, and also because reference demands initialization lits
{
	this->x = x;
	this->y = y;
	this->z = z;
	//this->shader = shader;

	VertexBuffer vbo(vertices, sizeof(vertices));
	ElementBuffer ebo(indices, sizeof(indices));

	vao.Link(vbo, 0);

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}

void Block::Draw()
{
	shader.Load();
	vao.Bind();
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, nullptr);
}
