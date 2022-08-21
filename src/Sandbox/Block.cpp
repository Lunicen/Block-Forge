//#define STB_IMAGE_IMPLEMENTATION
#include "Block.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>



Block::Block(const float x, const float y, const float z, Shader& shader, Texture& texture) : _shader(shader), _texture(texture)
{
#pragma region vao & vbo
	//_vao.Link(_vbo, 0, 3, 6,3);
	//_vao.Link(_vbo, 1, 3, 6,6);

	//_vao.Link(_vbo, 0, 3, 6,0);
	//_vao.Link(_vbo, 1, 3, 6,3);

	_vao.Link(_vbo, 0, 3, 5, 0);
	_vao.Link(_vbo, 1, 2, 5, 3);

	_vao.Unbind();
	_vbo.Unbind();
	_ebo.Unbind();

	Move(x, y, z);
#pragma endregion

#pragma region Textures
	/*
	stbi_set_flip_vertically_on_load(true);

	glGenTextures(1, &texture); //1 texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	//min & mag filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint tex0Uni = glGetUniformLocation(shader.GetProgram(), "tex0");
	shader.Load();
	glUniform1i(tex0Uni, 0);
	*/



	//glDeleteTextures(1, &texture); //trzeba bedzie to gdzies usuwac tylko nwm gdzie sa destruktory klockow... albo wogóle gdzie to powinno byæ w teorii po g³ównej pêtli programu???
#pragma endregion

#pragma region Textures_v2



#pragma endregion
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

	//texture
	_texture.Bind();
	//end of texture

	glDrawElements(GL_TRIANGLES, sizeof _indices / sizeof(GLuint), GL_UNSIGNED_INT, nullptr);
}

Shader Block::GetShader() const
{
	return _shader;
}
