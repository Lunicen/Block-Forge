#include "ChunkPlacer.h"

#include "Core/EngineExceptions.h"

std::unique_ptr<Order> ChunkPlacer::GetRenderView(const OrderType orderType)
{
	switch (orderType)
	{
		case OrderType::diamond:		return std::make_unique<DiamondOrder>(_renderDistance, _chunkSize);
		case OrderType::cube:			return std::make_unique<CubeOrder>(_renderDistance, _chunkSize);
		case OrderType::tiltedCube:		return std::make_unique<TiltedCubeOrder>(_renderDistance, _chunkSize);
	}

	throw UnknownValueException("The provided Render View type is not defined!");
}

ChunkPlacer::ChunkPlacer(const OrderType orderType, const size_t chunkSize, const size_t renderDistance, Camera& camera)
	: _camera(camera), _renderDistance(renderDistance), _chunkSize(chunkSize), _orderType(orderType)
{
}

void ChunkPlacer::Update() const
{
	_renderer->Render();
}

void ChunkPlacer::Bind(const std::shared_ptr<WorldGenerator>& worldGenerator)
{
	auto view = GetRenderView(_orderType);
	_renderer = std::make_unique<ChunkRenderer>(*worldGenerator, view, _camera);
}