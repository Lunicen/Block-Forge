#include "Chunk.h"


Chunk::Chunk(const size_t chunkSize, BlockMap& blockMap) : _mesh(blockMap.GetBlocksShader(), chunkSize)
{
	_blocks.resize(chunkSize * chunkSize * chunkSize);
}

void Chunk::LoadBlocks(const ChunkBlocks& blocks)
{
	_blocks = blocks;
}

void Chunk::LoadMesh(const std::vector<Vertex>& precalculatedMesh)
{
	_mesh.Rebuild(precalculatedMesh);
}

Chunk::Chunk(const ChunkFrame frame, ChunkBlocks blocks, BlockMap& blockMap) : _mesh(blockMap.GetBlocksShader(), frame.size), _blocks(std::move(blocks))
{
}

Chunk::Chunk(
	const ChunkFrame frame, 
	ChunkBlocks blocks,
	BlockMap& blockMap, 
	const std::vector<Vertex>& precalculatedMesh)
: _mesh(precalculatedMesh, blockMap.GetBlocksShader(), frame.size), _blocks(std::move(blocks))
{
}

void Chunk::Draw(const TextureAtlas& blockTexture, const Camera& camera)
{
	_mesh.Draw(blockTexture, camera);
}
