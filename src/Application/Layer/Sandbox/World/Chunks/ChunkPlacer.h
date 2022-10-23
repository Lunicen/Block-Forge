#pragma once
#include <future>

#include "Application/Layer/Sandbox/Camera.h"
#include "Application/Layer/Sandbox/World/WorldGenerator.h"
#include "OrderType/OrderTypes.h"
#include "Structure/Chunk.h"

/// @class ChunkPlacer
/// @brief Handles placing the chunks around the camera.
///	@details This class handles @see Chunk objects and manages them for optimal experience.
class ChunkPlacer
{
	Log& _log = Log::Get();

	std::vector<std::future<std::pair<ChunkFrame, ChunkBlocks>>> _futures;
	std::vector<std::future<void>> _futuresPool;

	std::shared_ptr<WorldGenerator> _generator;
	std::vector<std::pair<ChunkFrame, ChunkBlocks>> _chunksToBeBuildQueue;

	std::unique_ptr<Order> _order;

	Position _previousNormalizedPosition = {};
	std::unordered_map<Position, std::unique_ptr<Chunk>> _loadedChunks;

	static std::vector<Position> Subtract(const std::vector<Position>& aSet, const std::vector<Position>& bSet);
	Position GetNormalizedPosition(const Point3D& position, const size_t& chunkSize) const;
	std::string PositionToString(const Position& position) const;

	static void UpdateLoadedChunksVector(std::vector<std::future<std::pair<ChunkFrame, ChunkBlocks>>>* futuresQueue, std::vector<std::pair<ChunkFrame, ChunkBlocks>>* chunksToBuildQueue);
	static std::pair<ChunkFrame, ChunkBlocks> GetChunkAt(Position origin, const size_t size, const std::shared_ptr<WorldGenerator> generator);
	void BuildChunksInQueue();

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

	/// @brief Returns the map of placed chunks.
	std::unordered_map<Position, std::unique_ptr<Chunk>>& GetChunks();
};

