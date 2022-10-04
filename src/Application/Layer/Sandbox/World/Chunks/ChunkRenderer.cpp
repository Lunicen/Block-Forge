#include "ChunkRenderer.h"

ChunkRenderer::ChunkRenderer()
{
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void ChunkRenderer::Render(const std::unordered_map<Position, std::unique_ptr<Chunk>>& chunks, TextureAtlas& blocksTexture, const Camera& camera) const
{
	glEnable(GL_CULL_FACE);

	for (const auto& chunk : chunks)
	{
		chunk.second->Draw(blocksTexture, camera);
	}

	glDisable(GL_CULL_FACE);
}
