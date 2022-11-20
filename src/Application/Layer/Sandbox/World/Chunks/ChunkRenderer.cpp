#include "ChunkRenderer.h"

ChunkRenderer::ChunkRenderer()
{
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void ChunkRenderer::Render(const HashMap<Position, std::unique_ptr<Chunk>>& chunks, const TextureAtlas& blocksTexture, const Camera& camera) const
{
	glEnable(GL_CULL_FACE);

	for (const auto& chunk : chunks)
	{
		chunk.second->Draw(blocksTexture, camera);
	}

	glDisable(GL_CULL_FACE);
}
