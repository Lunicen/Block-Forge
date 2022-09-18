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
	if (_blockFaces.size() > 0)
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
	for (size_t x = 0; x < _frame.size; ++x)
	{
		for (size_t y = 0; y < _frame.size; ++y)
		{
			for (size_t z = 0; z < _frame.size; ++z)
			{
				//DrawBlockIfExists(x, y, z);
			}
		}
	}
}

glm::ivec3 Chunk::GetOrigin() const
{
	return _frame.origin;
}
