#include "Chunk.h"

#include "Core/EngineExceptions.h"

void Chunk::UpdateFacesMap(glm::ivec3 origin, const std::shared_ptr<BlockModel>& block, const FacesVisibility& visibility)
{
	auto& faces = _blockFaces[block];

	if (visibility.front)  faces.front.emplace_back(origin);
	if (visibility.back)   faces.back.emplace_back(origin);
	if (visibility.left)   faces.left.emplace_back(origin);
	if (visibility.right)  faces.right.emplace_back(origin);
	if (visibility.top)    faces.top.emplace_back(origin);
	if (visibility.bottom) faces.bottom.emplace_back(origin);
}

void Chunk::Initialize()
{
	if (!_blockFaces.empty())
	{
		throw BadInitializationException("Chunk was already initialized!");
	}

	for (auto& block : _blocks.block)
	{
		UpdateFacesMap(block.first, block.second.model, block.second.visibility);
	}
}

Chunk::Chunk(const ChunkFrame& frame, ChunkBlocks blocks, Camera& camera)
	: _frame(frame), _blocks(std::move(blocks)), _camera(camera)
{
	Initialize();
}

void Chunk::Draw() const
{
	for (auto& block : _blockFaces)
	{
		block.first->DrawFront (block.second.front, _camera);
		block.first->DrawBack  (block.second.back, _camera);
		block.first->DrawLeft  (block.second.left, _camera);
		block.first->DrawRight (block.second.right, _camera);
		block.first->DrawTop   (block.second.top, _camera);
		block.first->DrawBottom(block.second.bottom, _camera);
	}
}

glm::ivec3 Chunk::GetOrigin() const
{
	return _frame.origin;
}
