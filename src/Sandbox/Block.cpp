#include "Block.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>


Block::Block(const float x, const float y, const float z, Shader& shader) : _shader(shader)
{
	constexpr auto vertexSize = 3;
	_vao.Link(_vbo, vertexSize, 0);

	_vao.Unbind();
	_vbo.Unbind();
	_ebo.Unbind();

	Move(x, y, z);
}

void Block::Move(const float x, const float y, const float z)
{
	const auto origin = glm::mat4(1.0f);
	const auto moveTo = glm::vec3(x, y, z);

	_position = translate(origin, moveTo);
}

void Block::Draw() const
{
	glUniformMatrix4fv(glGetUniformLocation(_shader.GetProgram(), "position"), 1, GL_FALSE, value_ptr(_position));

	_vao.Bind();
	glDrawElements(GL_TRIANGLES, sizeof _indices / sizeof(GLuint), GL_UNSIGNED_INT, nullptr);
}

Shader& Block::GetShader() const
{
	return _shader;
}
