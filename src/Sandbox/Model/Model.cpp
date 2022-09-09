#include "Model.h"

Model::Model(const Mesh& mesh, Texture texture, const Camera& camera)
	: _mesh(std::make_unique<Mesh>(mesh.GetVertices(), mesh.GetIndices(), mesh.GetShader())),
	  _texture(std::move(texture)),
	  _camera(camera)
{
}

void Model::Draw(const glm::vec3 origin) const
{
	const auto& shader = _mesh->GetShader();
	const auto& indices = _mesh->GetIndices();

	_texture.TexUnit(shader);
	_texture.Bind();

	_camera.Bind(shader);

	const auto position = translate(glm::mat4(1.0f), origin);
	glUniformMatrix4fv(glGetUniformLocation(shader.GetProgram(), "position"), 1, GL_FALSE, value_ptr(position));

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
}
