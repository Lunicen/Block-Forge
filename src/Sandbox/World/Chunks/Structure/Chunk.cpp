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

	for (auto& block : _blockFaces)
	{
		auto& model = block.first;

		model->SetFrontFaces (_blockFaces[model].front, _frame.size);
		model->SetBackFaces  (_blockFaces[model].back, _frame.size);
		model->SetLeftFaces  (_blockFaces[model].left, _frame.size);
		model->SetRightFaces (_blockFaces[model].right, _frame.size);
		model->SetTopFaces   (_blockFaces[model].top, _frame.size);
		model->SetBottomFaces(_blockFaces[model].bottom, _frame.size);
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
		block.first->Draw(_camera);
	}
}

glm::ivec3 Chunk::GetOrigin() const
{
	return _frame.origin;
}
