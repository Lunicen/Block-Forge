#include "Chunk.h"


Chunk::Chunk(const size_t& size, std::shared_ptr<Texture> blocksTexture, Shader& shader) :
	_mesh(ChunkMesh(shader, size)), _blockTexture(std::move(blocksTexture))
{
}

Chunk::Chunk(ChunkBlocks blocks, std::shared_ptr<Texture> blocksTexture, const size_t& size, Shader& shader) : _mesh(ChunkMesh(shader, size)), _blockTexture(
	std::move(blocksTexture)), _blocks(std::move(blocks))
{
	_mesh.Rebuild(_blocks);
}

void Chunk::Draw(const Camera& camera) const
{
	_mesh.Draw(*_blockTexture, camera);
}
