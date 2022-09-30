#include "Chunk.h"


Chunk::Chunk(const size_t& size, Texture& blocksTexture, Shader& shader) : _mesh(ChunkMesh(shader, size)), _blockTexture(blocksTexture)
{
}

Chunk::Chunk(ChunkBlocks blocks, Texture& blocksTexture, const size_t& size, Shader& shader) : _mesh(ChunkMesh(shader, size)), _blockTexture(blocksTexture), _blocks(std::move(blocks))
{
}

void Chunk::Draw(const Camera& camera) const
{
	_mesh.Draw(_blockTexture, camera);
}
