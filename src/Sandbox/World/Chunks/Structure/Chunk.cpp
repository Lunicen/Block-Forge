#include "Chunk.h"


Chunk::Chunk(const ChunkFrame& frame, ChunkBlocks blocks, Camera& camera)
	: _frame(frame), _blocks(std::move(blocks)), _camera(camera)
{
}

void Chunk::Draw() const
{
	for (auto& block : _blocks.block)
	{
		auto origin = block.first;

		const auto& blockModel = block.second.model;
		const auto& faceVisible = block.second.visibility;

		if (faceVisible.front)  blockModel->DrawFrontFace(origin, _camera);
		if (faceVisible.back)   blockModel->DrawBackFace(origin, _camera);
		if (faceVisible.left)   blockModel->DrawLeftFace(origin, _camera);
		if (faceVisible.right)  blockModel->DrawRightFace(origin, _camera);
		if (faceVisible.top)    blockModel->DrawTopFace(origin, _camera);
		if (faceVisible.bottom) blockModel->DrawBottomFace(origin, _camera);
	}
}

glm::ivec3 Chunk::GetOrigin() const
{
	return _frame.origin;
}
