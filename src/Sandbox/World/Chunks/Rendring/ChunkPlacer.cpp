#include "ChunkPlacer.h"

#include "Core/EngineExceptions.h"
#include "RenderViews/RenderViewTypes.h"

std::unique_ptr<RenderView> ChunkPlacer::GetRenderView(const RenderViewType viewType)
{
	switch (viewType)
	{
		case RenderViewType::diamond:		return std::make_unique<DiamondView>(_renderDistance, _chunkSize);
		case RenderViewType::cube:			return std::make_unique<CubeView>(_renderDistance, _chunkSize);
		case RenderViewType::tiltedCube:	return std::make_unique<TiltedCube>(_renderDistance, _chunkSize);
	}

	throw UnknownValueException("The provided Render View type is not defined!");
}

ChunkPlacer::ChunkPlacer(const RenderViewType viewType, const size_t chunkSize, const size_t renderDistance, Camera& camera)
	: _camera(camera), _renderDistance(renderDistance), _chunkSize(chunkSize), _viewType(viewType)
{
}

void ChunkPlacer::Update() const
{
	_renderer->Render();
}

void ChunkPlacer::Bind(const std::shared_ptr<WorldGenerator>& worldGenerator)
{
	auto view = GetRenderView(_viewType);
	_renderer = std::make_unique<ChunkRenderer>(*worldGenerator, view, _camera);
}