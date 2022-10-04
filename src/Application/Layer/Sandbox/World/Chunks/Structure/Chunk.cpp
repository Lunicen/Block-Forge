#include "Chunk.h"


Chunk::Chunk(ChunkBlocks blocks, BlockMap& blockMap, const size_t& size) : _mesh(ChunkMesh(blockMap.GetBlocksShader(), size)), _blocks(std::move(blocks))
{
	_mesh.Rebuild(_blocks, blockMap);
}

void Chunk::Draw(const TextureAtlas& blockTexture, const Camera& camera) const
{
	_mesh.Draw(blockTexture, camera);
}
