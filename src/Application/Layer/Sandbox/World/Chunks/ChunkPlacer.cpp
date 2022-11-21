#include "ChunkPlacer.h"

#include "Structure/ChunkMeshUtils.h"

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

void ChunkPlacer::AddNewChunks(const std::vector<Position>& currentChunkOrigins)
{
	const auto size = _order->GetChunkSize();

	for(auto origin : currentChunkOrigins)
	{
		if (_hasPositionChanged || !_running)
		{
			break;
		}

		{
			const std::lock_guard<std::mutex> lock(_chunksMutex);

			if (_chunksPositionsAroundCamera.find(origin) == _chunksPositionsAroundCamera.end() || 
				_loadedChunks.find(origin) != _loadedChunks.end())
			{
				continue;
			}
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
			[=](const Position& a, const Position& b) -> bool
			{
				const auto origin = Point3D(lastRememberedPosition);
				return distance(origin, Point3D(a)) < distance(origin, Point3D(b));
			});

		_hasPositionChanged = false;
		AddNewChunks(currentChunksOrigins);
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

	case OrderType::shortOval:
		_order = std::make_unique<ShortOvalOrder>(renderDistance, chunkSize);
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
	if (static_cast<double>(_freeChunks.size()) / static_cast<double>(_freeChunks.capacity()) < 0.25)
	{
		RemoveStaleChunk();
	}

	if (!_chunksToLoad.empty())
	{
		bool firstConditionSucceed = false;
		const auto position = std::get<0>(*_chunksToLoad.front());

		{
			const std::lock_guard<std::mutex> lock(_chunksMutex);

			if (_chunksPositionsAroundCamera.find(position) == _chunksPositionsAroundCamera.end() ||
			_loadedChunks.find(position) != _loadedChunks.end())
			{
				_chunksToLoad.pop();
				firstConditionSucceed = true;
			}
		}

		if (!firstConditionSucceed && _chunksPositionsAroundCamera.find(position) != _chunksPositionsAroundCamera.end())
		{
			const auto data = *_chunksToLoad.front();

			if (_freeChunks.empty())
			{
				RemoveStaleChunk();
			}

			auto chunk = std::move(_freeChunks.back());
			_freeChunks.pop_back();

			const auto& origin = std::get<0>(data);
			const auto& blocks = std::get<1>(data);
			const auto& mesh = std::get<2>(data);

			chunk->LoadBlocks(blocks);
			chunk->LoadMesh(mesh);

			_loadedChunks[origin] = std::move(chunk);
			
			_chunksToLoad.pop();
		}
	}
	else
	{
		if (_freeChunks.size() < _freeChunks.capacity() - _chunksPositionsAroundCamera.size())
		{
			RemoveStaleChunk();
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
