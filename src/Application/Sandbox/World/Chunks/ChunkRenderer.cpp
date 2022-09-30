#include "ChunkRenderer.h"

ChunkRenderer::ChunkRenderer()
{
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void ChunkRenderer::Render(const std::unordered_map<Position, std::unique_ptr<Chunk>>& chunks, const Camera& camera) const
{
	glEnable(GL_CULL_FACE);

	for (const auto& chunk : chunks)
	{
		chunk.second->Draw(camera);
	}

	glDisable(GL_CULL_FACE);
}
