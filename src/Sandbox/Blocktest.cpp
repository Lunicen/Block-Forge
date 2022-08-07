#include "Blocktest.h"



Blocktest::Blocktest(float x, float y, float z) //there must be initialization list otherwise memory will be used more, and also because reference demands initialization lits
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
}

void Blocktest::Draw()
{
	vao.Bind();
	glPushMatrix();
	glTranslatef(x, y, z); //TODO sprawdziæ czy nie lepiej +x, +y, +z
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, nullptr);
	//glTranslatef(-x, -y, -z);
	glPopMatrix();
}
