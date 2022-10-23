#include "Chunk.h"


Chunk::Chunk(const ChunkFrame frame, ChunkBlocks blocks, BlockMap& blockMap) : _mesh(ChunkMesh(blockMap.GetBlocksShader(), frame.size)), _blocks(std::move(blocks))
{
	_mesh.Rebuild(frame, _blocks, blockMap);
}

Chunk::Chunk(
	const ChunkFrame frame, 
	ChunkBlocks blocks,
	BlockMap& blockMap, 
	const std::vector<Vertex>& precalculatedMesh)
: _mesh(precalculatedMesh, blockMap.GetBlocksShader(), frame.size), _blocks(std::move(blocks))
{
}

void Chunk::Draw(const TextureAtlas& blockTexture, const Camera& camera) const
{
	_mesh.Draw(blockTexture, camera);
}
