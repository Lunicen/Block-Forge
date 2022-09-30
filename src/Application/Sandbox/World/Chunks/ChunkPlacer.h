#pragma once
#include "ChunkBuilder.h"
#include "Application/Sandbox/Camera.h"
#include "Application/Sandbox/World/WorldGenerator.h"
#include "OrderType/OrderTypes.h"
#include "Structure/Chunk.h"

/// @class ChunkPlacer
/// @brief Handles placing the chunks around the camera.
///	@details This class handles @see Chunk objects and manages them for optimal experience.
class ChunkPlacer
{
	Log& _log = Log::Get();
	ChunkBuilder _chunkBuilder;

	std::shared_ptr<WorldGenerator> _generator;
	std::unique_ptr<Order> _order;

	Position _previousNormalizedPosition = {};
	std::unordered_map<Position, std::unique_ptr<Chunk>> _loadedChunks = {};

	static std::vector<Position> Subtract(const std::vector<Position>& aSet, const std::vector<Position>& bSet);
	Position GetNormalizedPosition(const Point3D& position, const size_t& chunkSize) const;
	std::string PositionToString(const Position& position) const;

	void RemoveStaleChunks(const std::vector<Position>& currentChunksOrigins);
	void AddNewChunks(const std::vector<Position>& currentChunksOrigins);

	void UpdateChunksAround(const Position& normalizedOrigin);

public:

	/// @brief The constructor.
	/// @param orderType - the way the chunks will be generated.
	///	@param chunkSize - the size of the generated chunks.
	///	@param renderDistance - specifies the maximum distance from the camera to render.
	///	@param initPosition - position in space from where initialize the chunk placer.
	ChunkPlacer(OrderType orderType, size_t chunkSize, size_t renderDistance, const Position& initPosition);

	/// @brief Updates the chunk placer to adapt to the current frame.
	///	@param position - Position around which chunks are going to be placed.
	void Update(const Position& position);

	/// @brief Binds world generator to the chunk placer.
	///	@details The world generator is used to define how the world is generated, when
	///	this class handles only displaying it in an optimal way.
	///	@param generator - reference to the world generator.
	void Bind(std::shared_ptr<WorldGenerator> generator);

	std::unordered_map<Position, std::unique_ptr<Chunk>>& GetChunks();
	
};

