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

		const auto& faceModel = block.second.model;
		const auto& faceVisible = block.second.visibility;

		if (faceVisible.front)  faceModel->DrawFrontFace(origin, _camera);
		if (faceVisible.back)   faceModel->DrawBackFace(origin, _camera);
		if (faceVisible.left)   faceModel->DrawLeftFace(origin, _camera);
		if (faceVisible.right)  faceModel->DrawRightFace(origin, _camera);
		if (faceVisible.top)    faceModel->DrawTopFace(origin, _camera);
		if (faceVisible.bottom) faceModel->DrawBottomFace(origin, _camera);
	}
}

glm::ivec3 Chunk::GetOrigin() const
{
	return _frame.origin;
}
