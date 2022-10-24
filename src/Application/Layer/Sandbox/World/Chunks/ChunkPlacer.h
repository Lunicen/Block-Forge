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
	
	static std::mutex _chunksQueueMutex;
	static std::mutex _cleanupFuturesMutex;

	static std::vector<std::future<void>> _futures;
	static std::vector<std::future<void>> _globalFutures;

	static std::shared_ptr<WorldGenerator> _generator;
	static std::vector<std::tuple<Position, ChunkBlocks, std::vector<Vertex>>> _newChunksQueue;
	static std::vector<Position> _staleChunksQueue;

	static std::unique_ptr<Order> _order;

	Position _previousNormalizedPosition = {};
	static std::vector<std::unique_ptr<Chunk>> _freeChunks;
	static std::unordered_map<Position, std::unique_ptr<Chunk>> _loadedChunks;
	
	Position GetNormalizedPosition(const Point3D& position, const size_t& chunkSize) const;
	std::string PositionToString(const Position& position) const;

	static void BuildChunkAt(Position origin, size_t size, const std::shared_ptr<WorldGenerator>& generator);
	void BuildNewChunks() const;

	static void RemoveStaleChunksAround(Position normalizedOrigin);
	static void AddNewChunksAround(Position normalizedOrigin);
	void RemoveStaleChunks() const;

	static void UpdateChunksAround(const Position& normalizedOrigin);
	static void CleanupStaleFutures();

public:

	/// @brief The constructor.
	/// @param orderType - the way the chunks will be generated.
	///	@param chunkSize - the size of the generated chunks.
	///	@param renderDistance - specifies the maximum distance from the camera to render.
	///	@param initPosition - position in space from where initialize the chunk placer.
	ChunkPlacer(OrderType orderType, size_t chunkSize, size_t renderDistance, const Position& initPosition);

	/// @brief Updates the chunk placer to adapt to the current frame.
	void Update() const;

	/// @brief Adapts chunk placer to the camera position.
	///	@param position - Position around which chunks are going to be placed.
	void ReactToCameraMovement(const Position& position);

	/// @brief Binds world generator to the chunk placer.
	///	@details The world generator is used to define how the world is generated, when
	///	this class handles only displaying it in an optimal way.
	///	@param generator - reference to the world generator.
	void Bind(std::shared_ptr<WorldGenerator> generator, size_t chunkSize) const;

	/// @brief Returns the map of placed chunks.
	static std::unordered_map<Position, std::unique_ptr<Chunk>>& GetChunks();

	static std::mutex& GetMutex();

	/// @brief Terminates the chunk placer.
	static void Terminate();
};

