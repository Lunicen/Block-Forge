#include "ChunkRenderer.h"

ChunkRenderer::ChunkRenderer(ChunkPlacer& chunkPlacer) : _chunkPlacer(chunkPlacer)
{
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
}

void ChunkRenderer::Render(const Camera& camera) const
{
	glEnable(GL_CULL_FACE);

	const auto& chunks = _chunkPlacer.GetChunks();
	for (const auto& chunk : chunks)
	{
		chunk.second.Draw(camera);
	}

	glDisable(GL_CULL_FACE);
}
