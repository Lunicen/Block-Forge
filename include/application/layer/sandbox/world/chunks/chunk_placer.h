#pragma once
#include "application/layer/sandbox/camera.h"
#include "application/layer/sandbox/world/world_generator.h"
#include "application/layer/sandbox/world/chunks/order_type/order_types.h"
#include "rigtorp/SPSCQueue.h"
#include "structure/chunk.h"

/// @class ChunkPlacer
/// @brief Handles placing the chunks around the camera.
///	@details This class handles @see Chunk objects and manages them for optimal experience.
class ChunkPlacer
{
	static Log& _log;

	std::unique_ptr<std::jthread> _lazyLoader{};

	static std::mutex _chunksMutex;
	static std::atomic<bool> _hasPositionChanged;
	static std::condition_variable _lazyLoaderLock;
	static std::atomic<bool> _isLazyLoaderWaiting;
	static std::atomic<bool> _running;

	static rigtorp::SPSCQueue<std::tuple<Position, ChunkBlocks, std::vector<Vertex>>> _chunksToLoad;
	static std::vector<std::unique_ptr<Chunk>> _freeChunks;
	static HashMap<Position, std::unique_ptr<Chunk>> _loadedChunks;

	static Position _previousNormalizedPosition;

	static std::shared_ptr<WorldGenerator> _generator;
	static std::unique_ptr<Order> _order;

	static HashSet<Position> _chunksPositionsAroundCamera;

	Position GetNormalizedPosition(const Point3D& position, const size_t& chunkSize) const;
	std::string PositionToString(const Position& position) const;

	static bool IsChunkInCameraRange(Position origin);
	static void AddNewChunks(const std::vector<Position>& currentChunkOrigins);
	static void LazyLoader();

	void RemoveStaleChunksFromChunksToLoadQueue(Position position) const;
	void RemoveStaleChunk() const;

public:

	/// @brief The constructor.
	/// @param orderType - the way the chunks will be generated.
	///	@param chunkSize - the size of the generated chunks.
	///	@param renderDistance - specifies the maximum distance from the camera to render.
	///	@param initPosition - position in space from where initialize the chunk placer.
	ChunkPlacer(OrderType orderType, size_t chunkSize, size_t renderDistance, const Position& initPosition);

	/// @brief Adapts chunk placer to the camera position.
	///	@param position - Position around which chunks are going to be placed.
	void ReactToCameraMovement(const Position& position) const;

	/// @brief Binds world generator to the chunk placer.
	///	@details The world generator is used to define how the world is generated, when
	///	this class handles only displaying it in an optimal way.
	///	@param generator - reference to the world generator.
	///	@param chunkSize - size of a chunk.
	void Bind(const std::shared_ptr<WorldGenerator>& generator, size_t chunkSize);

	/// @brief Returns the map of placed chunks.
	HashMap<Position, std::unique_ptr<Chunk>>& GetChunks() const;

	/// @brief Terminates the chunk placer.
	void Terminate() const;
};

