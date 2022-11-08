#include "ChunkPlacer.h"

#include "Structure/ChunkMeshUtils.h"

Log& ChunkPlacer::_log = Log::Get();

std::mutex ChunkPlacer::_chunksMutex;
std::atomic<bool> ChunkPlacer::_hasPositionChanged;
std::atomic<bool> ChunkPlacer::_allChunkAroundAreLoaded;
std::condition_variable ChunkPlacer::_lazyLoaderLock;
std::atomic<bool> ChunkPlacer::_running;
std::atomic<bool> ChunkPlacer::_isLazyLoaderWaiting;

std::vector<std::tuple<Position, ChunkBlocks, std::vector<Vertex>>> ChunkPlacer::_chunksToLoad = {};
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

void ChunkPlacer::AddNewChunks(const HashSet<Position>& currentChunkOrigins)
{
	const auto size = _order->GetChunkSize();

	for(auto origin : currentChunkOrigins)
	{
		if (_hasPositionChanged || !_running)
		{
			break;
		}

		if (_loadedChunks.find(origin) == _loadedChunks.end())
		{
			const auto chunkFrame = ChunkFrame{origin, size};

			ChunkBlocks chunkBlocks;
			chunkBlocks.resize(size * size * size);
			
			_generator->PaintChunk(chunkFrame, chunkBlocks);

			auto mesh = ChunkMeshUtils::GetMeshVertices(chunkFrame, chunkBlocks, _generator->GetBlockMap());
			
			const std::lock_guard<std::mutex> lock(_chunksMutex);
			_chunksToLoad.emplace_back(origin, chunkBlocks, mesh);
		}
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

			std::unique_lock<std::mutex> loaderLock(_chunksMutex);
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

				if (!_allChunkAroundAreLoaded)
				{
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

		try
		{
			const auto currentChunksOrigins = _order->GetChunksAround(lastRememberedPosition);
			auto currentChunksOriginsSet = HashSet<Position>(currentChunksOrigins.begin(), currentChunksOrigins.end());
			
			AddNewChunks(currentChunksOriginsSet);
			_hasPositionChanged = false;
		}
		catch(const std::bad_alloc& exception)
		{
			_log.Error("Failed to allocate memory: " + std::string(exception.what()));
		}
	}
}

ChunkPlacer::ChunkPlacer(const OrderType orderType, const size_t chunkSize, const size_t renderDistance, const Position& initPosition)
{
	switch (orderType)
	{
	case OrderType::cube:	
		_order = std::make_unique<CubeOrder>(renderDistance, chunkSize);
		break;

	case OrderType::diamond: 
		_order = std::make_unique<DiamondOrder>(renderDistance, chunkSize);
		break;

	case OrderType::tiltedCube:	
		_order = std::make_unique<TiltedCubeOrder>(renderDistance, chunkSize);
		break;
	}

	_previousNormalizedPosition = GetNormalizedPosition(initPosition, chunkSize);
}

void ChunkPlacer::ReactToCameraMovement(const Position& position) const
{
	const auto currentNormalizedPosition = GetNormalizedPosition(position, _order->GetChunkSize());

	if (currentNormalizedPosition != _previousNormalizedPosition)
	{
		_previousNormalizedPosition = currentNormalizedPosition;

		auto chunksPositionsAroundCameraVector = _order->GetChunksAround(_previousNormalizedPosition);
		_chunksPositionsAroundCamera = HashSet<Position>(chunksPositionsAroundCameraVector.begin(), chunksPositionsAroundCameraVector.end());

		_hasPositionChanged = true;
		_allChunkAroundAreLoaded = false;

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

	_freeChunks.reserve(chunksToGenerate);
	_loadedChunks.reserve(chunksToGenerate);
	_chunksToLoad.reserve(chunksToGenerate);

	for (size_t i = 0; i < chunksToGenerate; ++i)
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
		const auto origin = chunksIterator->first;

		if (_chunksPositionsAroundCamera.find(origin) == _chunksPositionsAroundCamera.end())
		{
			auto handledChunk = std::move(_loadedChunks[origin]);
			_loadedChunks.erase(chunksIterator);

			_freeChunks.emplace_back(std::move(handledChunk));

			break;
		}

		chunksIterator++;
	}
}

HashMap<Position, std::unique_ptr<Chunk>>& ChunkPlacer::GetChunks() const
{
	if (!_chunksToLoad.empty())
	{
		const auto position = std::get<0>(_chunksToLoad.back());

		if (_chunksPositionsAroundCamera.find(position) == _chunksPositionsAroundCamera.end() ||
			_loadedChunks.find(position) != _loadedChunks.end())
		{
			const std::lock_guard<std::mutex> lock(_chunksMutex);
			while (!_chunksToLoad.empty() && 
					(_chunksPositionsAroundCamera.find(std::get<0>(_chunksToLoad.back())) != _chunksPositionsAroundCamera.end() || 
					_loadedChunks.find(position) != _loadedChunks.end())
				)
			{
				_chunksToLoad.pop_back();
			}
		}

		else if (!_freeChunks.empty() && _chunksPositionsAroundCamera.find(position) != _chunksPositionsAroundCamera.end())
		{
			const auto data = _chunksToLoad.back();

			auto chunk = std::move(_freeChunks.back());
			_freeChunks.pop_back();

			const auto& origin = std::get<0>(data);
			const auto& blocks = std::get<1>(data);
			const auto& mesh = std::get<2>(data);

			chunk->LoadBlocks(blocks);
			chunk->LoadMesh(mesh);

			_loadedChunks[origin] = std::move(chunk);

			const std::lock_guard<std::mutex> lock(_chunksMutex);
			_chunksToLoad.pop_back();
		}

		else
		{
			const std::lock_guard<std::mutex> lock(_chunksMutex);
			RemoveStaleChunk();
		}
	}
	else
	{
		if (_loadedChunks.size() > _chunksPositionsAroundCamera.size())
		{
			const std::lock_guard<std::mutex> lock(_chunksMutex);
			RemoveStaleChunk();
		}
		
		if (_isLazyLoaderWaiting && !_allChunkAroundAreLoaded)
		{
			_allChunkAroundAreLoaded = true;

			for (auto& chunk : _chunksPositionsAroundCamera)
			{
				const std::lock_guard<std::mutex> lock(_chunksMutex);
				if (_loadedChunks.find(chunk) == _loadedChunks.end())
				{
					_allChunkAroundAreLoaded = false;

					_lazyLoaderLock.notify_one();
					break;
				}
			}
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
