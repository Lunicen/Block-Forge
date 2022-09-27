#include "Chunk.h"


Chunk::Chunk()
{
}

Chunk::Chunk(ChunkBlocks blocks) : _blocks(std::move(blocks))
{
}

void Chunk::Draw(const Camera& camera) const
{
	for (auto& block : _blocks.block)
	{
		auto origin = block.first;

		const auto& blockModel = block.second.model;
		const auto& faceVisible = block.second.visibility;

		if (faceVisible.front)  blockModel->DrawFrontFace(origin, camera);
		if (faceVisible.back)   blockModel->DrawBackFace(origin, camera);
		if (faceVisible.left)   blockModel->DrawLeftFace(origin, camera);
		if (faceVisible.right)  blockModel->DrawRightFace(origin, camera);
		if (faceVisible.top)    blockModel->DrawTopFace(origin, camera);
		if (faceVisible.bottom) blockModel->DrawBottomFace(origin, camera);
	}
}
