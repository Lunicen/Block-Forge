#include "application/layer/sandbox/world/chunks/chunk_placer.h"

#include "application/layer/sandbox/world/chunks/structure/chunk_mesh_utils.h"

Log& ChunkPlacer::_log = Log::Get();

std::mutex ChunkPlacer::_chunksMutex;
std::atomic<bool> ChunkPlacer::_hasPositionChanged;
std::condition_variable ChunkPlacer::_lazyLoaderLock;
std::atomic<bool> ChunkPlacer::_running;
std::atomic<bool> ChunkPlacer::_isLazyLoaderWaiting;

rigtorp::SPSCQueue<std::tuple<Position, ChunkBlocks, std::vector<Vertex>>> ChunkPlacer::_chunksToLoad(10000);
std::vector<std::unique_ptr<Chunk>> ChunkPlacer::_freeChunks = {};
HashMap<Position, std::unique_ptr<Chunk>> ChunkPlacer::_loadedChunks = {};

Position ChunkPlacer::_previousNormalizedPosition = {};

std::shared_ptr<WorldGenerator> ChunkPlacer::_generator = nullptr;
std::unique_ptr<Order> ChunkPlacer::_order = nullptr;

HashSet<Position> ChunkPlacer::_chunksPositionsAroundCamera = {};

Position ChunkPlacer::GetNormalizedPosition(const Point3D& position, const size_t& chunkSize) const
{
	auto normalizedPosition = position;

	normalizedPosition /= chunkSize;

	normalizedPosition.x = floor(normalizedPosition.x);
	normalizedPosition.y = floor(normalizedPosition.y);
	normalizedPosition.z = floor(normalizedPosition.z);

	return {normalizedPosition};
}

std::string ChunkPlacer::PositionToString(const Position& position) const
{
	return std::to_string(position.x) + ", " + 
		   std::to_string(position.y) + ", " + 
		   std::to_string(position.z);
}

bool ChunkPlacer::IsChunkInCameraRange(const Position origin)
{
	const std::scoped_lock lock(_chunksMutex);

	if (_chunksPositionsAroundCamera.find(origin) == _chunksPositionsAroundCamera.end() || 
		_loadedChunks.find(origin) != _loadedChunks.end())
	{
		return true;
	}

	return false;
}

void ChunkPlacer::AddNewChunks(const std::vector<Position>& currentChunkOrigins)
{
	const auto size = _order->GetChunkSize();

	for(auto origin : currentChunkOrigins)
	{
		if (_hasPositionChanged || !_running)
		{
			break;
		}

		if (IsChunkInCameraRange(origin))
		{
			continue;
		}

		const auto chunkFrame = ChunkFrame{origin, size};

		ChunkBlocks chunkBlocks;
		chunkBlocks.resize(size * size * size);
		
		_generator->PaintChunk(chunkFrame, chunkBlocks);

		auto mesh = ChunkMeshUtils::GetMeshVertices(chunkFrame, chunkBlocks, _generator->GetBlockMap());
		
		_chunksToLoad.emplace(origin, chunkBlocks, mesh);
	}
}

void ChunkPlacer::LazyLoader()
{
	_running = true;
	auto lastRememberedPosition = _previousNormalizedPosition - 1;

	while (_running)
	{
		if (!_hasPositionChanged)
		{
			_isLazyLoaderWaiting = true;

			std::unique_lock loaderLock(_chunksMutex);
			_lazyLoaderLock.wait(loaderLock, [&lastRememberedPosition]
			{
				if (!_running)
				{
					return true;
				}

				if (lastRememberedPosition != _previousNormalizedPosition)
				{
					lastRememberedPosition = _previousNormalizedPosition;
					_hasPositionChanged = false;
					return true;
				}

				return false;
			});

			_isLazyLoaderWaiting = false;
		}
		else
		{
			lastRememberedPosition = _previousNormalizedPosition;
		}

		auto currentChunksOrigins = _order->GetChunksAround(lastRememberedPosition);
		std::sort(currentChunksOrigins.begin(), currentChunksOrigins.end(),
	    [=](const Position& a, const Position& b)
	    {
	        const auto origin = Point3D(lastRememberedPosition);
	        return distance(origin, Point3D(a)) < distance(origin, Point3D(b));
	    });

		_hasPositionChanged = false;
		AddNewChunks(currentChunksOrigins);
	}
}

void ChunkPlacer::RemoveStaleChunksFromChunksToLoadQueue(Position position) const
{
	const std::scoped_lock lock(_chunksMutex);

	while (
		!_chunksToLoad.empty() && (
		_chunksPositionsAroundCamera.find(position) == _chunksPositionsAroundCamera.end() ||
		_loadedChunks.find(position) != _loadedChunks.end()))
	{
		_chunksToLoad.pop();

		if (!_chunksToLoad.empty())
		{
			position = std::get<0>(*_chunksToLoad.front());
		}
	}
}

ChunkPlacer::ChunkPlacer(const OrderType orderType, const size_t chunkSize, const size_t renderDistance, const Position& initPosition)
{
	switch (orderType)
	{
	using enum OrderType;

	case cube:	
		_order = std::make_unique<CubeOrder>(renderDistance, chunkSize);
		break;

	case diamond: 
		_order = std::make_unique<DiamondOrder>(renderDistance, chunkSize);
		break;

	case tiltedCube:	
		_order = std::make_unique<TiltedCubeOrder>(renderDistance, chunkSize);
		break;

	case shortOval:
		_order = std::make_unique<ShortOvalOrder>(renderDistance, chunkSize);
		break;
	}

	_previousNormalizedPosition = GetNormalizedPosition(initPosition, chunkSize);
}

void ChunkPlacer::ReactToCameraMovement(const Position& position) const
{
	if (const auto currentNormalizedPosition = GetNormalizedPosition(position, _order->GetChunkSize()); currentNormalizedPosition != _previousNormalizedPosition)
	{
		_previousNormalizedPosition = currentNormalizedPosition;

		auto chunksPositionsAroundCameraVector = _order->GetChunksAround(_previousNormalizedPosition);
		_chunksPositionsAroundCamera = HashSet<Position>(chunksPositionsAroundCameraVector.begin(), chunksPositionsAroundCameraVector.end());

		_hasPositionChanged = true;

		_lazyLoaderLock.notify_one();

		_log.Trace("Normalized position: " + PositionToString(currentNormalizedPosition));
	}
}

void ChunkPlacer::Bind(const std::shared_ptr<WorldGenerator>& generator, const size_t chunkSize)
{
	if (_generator != nullptr)
	{
		while (!_loadedChunks.empty())
		{
			_loadedChunks.erase(_loadedChunks.begin());
		}

		while (!_freeChunks.empty())
		{
			_freeChunks.pop_back();
		}
	}

	_generator = generator;

	const auto& chunksToGenerate = _order->GetChunksAmount() * 2;
	constexpr auto additionalFreeChunksFactor = 2;

	_freeChunks.reserve(chunksToGenerate * additionalFreeChunksFactor);
	_loadedChunks.reserve(chunksToGenerate);

	for (size_t i = 0; i < chunksToGenerate * additionalFreeChunksFactor; ++i)
	{
		_freeChunks.emplace_back(std::make_unique<Chunk>(chunkSize, _generator->GetBlockMap()));
	}

	auto chunksPositionsAroundCameraVector = _order->GetChunksAround(_previousNormalizedPosition);
	_chunksPositionsAroundCamera = HashSet<Position>(chunksPositionsAroundCameraVector.begin(), chunksPositionsAroundCameraVector.end());

	_lazyLoader = std::make_unique<std::thread>(&LazyLoader);
}

void ChunkPlacer::RemoveStaleChunk() const
{
	auto chunksIterator = _loadedChunks.begin();

	while (chunksIterator != _loadedChunks.end())
	{
		if (const auto origin = chunksIterator->first; _chunksPositionsAroundCamera.find(origin) == _chunksPositionsAroundCamera.end())
		{
			auto handledChunk = std::move(_loadedChunks[origin]);
			_loadedChunks.erase(chunksIterator);

			_freeChunks.emplace_back(std::move(handledChunk));

			break;
		}

		++chunksIterator;
	}
}

HashMap<Position, std::unique_ptr<Chunk>>& ChunkPlacer::GetChunks() const
{
	if (_freeChunks.size() - _chunksPositionsAroundCamera.size() > 0)
	{
		RemoveStaleChunk();
	}

	if (!_chunksToLoad.empty())
	{
		const auto [position, chunkBlocks, vertices] = *_chunksToLoad.front();
		RemoveStaleChunksFromChunksToLoadQueue(position);

		if (!_chunksToLoad.empty() && _chunksPositionsAroundCamera.find(position) != _chunksPositionsAroundCamera.end())
		{
			if (_freeChunks.empty())
			{
				RemoveStaleChunk();
			}

			auto chunk = std::move(_freeChunks.back());
			_freeChunks.pop_back();

			const auto& origin = position;
			const auto& blocks = chunkBlocks;
			const auto& mesh = vertices;

			chunk->LoadBlocks(blocks);
			chunk->LoadMesh(mesh);

			_loadedChunks[origin] = std::move(chunk);
			
			_chunksToLoad.pop();
		}
	}

	return _loadedChunks;
}

void ChunkPlacer::Terminate() const
{
	_running = false;
	_lazyLoaderLock.notify_one();
	_lazyLoader->join();

	_generator = nullptr;
}
