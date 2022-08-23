#include "ChunkManager.h"

#include "Sandbox/Utils/ChunkUtils.h"

glm::ivec3 ChunkManager::GetNormalizedPosition(glm::vec3 position) const
{
	position /= _chunkSize;
	position -= 0.5f;

	return {
		ceil(position.x),
		ceil(position.y),
		ceil(position.z)
	};
}

unsigned ChunkManager::CountChunksRecursive(const unsigned level)
{
	const auto result = 4 * level;

	if (result == 0) return 1;
	return result + CountChunksRecursive(level - 1);
}

void ChunkManager::RemoveExcludedChunks(const std::vector<glm::ivec3>& oldOrigins)
{
	

	for (const auto& oldOrigin : oldOrigins)
	{
		if (std::find(_loadedChunksOrigin.begin(), _loadedChunksOrigin.end(), oldOrigin) != _loadedChunksOrigin.end())
		{
			_log.Trace("Reusing chunk: " + 
					   std::to_string(oldOrigin.x) + ", " + 
					   std::to_string(oldOrigin.y) + ", " + 
					   std::to_string(oldOrigin.z));

			continue;
		}

		auto outdatedChunk = std::find_if(
			_loadedChunks.begin(), 
			_loadedChunks.end(),
			[&](const std::unique_ptr<Chunk>& chunk)
			{
				return chunk->GetOrigin() == oldOrigin * _chunkSize;
			}
		);

		if (outdatedChunk != _loadedChunks.end())
		{
			_log.Trace("Removed chunk: " + 
					   std::to_string(oldOrigin.x) + ", " + 
					   std::to_string(oldOrigin.y) + ", " + 
					   std::to_string(oldOrigin.z));

			_loadedChunks.erase(outdatedChunk);
		}
	}
}

void ChunkManager::AddChunkToListIfIsNew(const glm::ivec3& currentOrigin, const std::vector<glm::ivec3>& oldOrigins)
{
	if (std::find(oldOrigins.begin(), oldOrigins.end(), currentOrigin) == oldOrigins.end())
	{
		_log.Trace("Added chunk: " + 
			   std::to_string(currentOrigin.x) + ", " + 
			   std::to_string(currentOrigin.y) + ", " + 
			   std::to_string(currentOrigin.z));

		auto chunk = std::make_unique<Chunk>(currentOrigin, *this);
		auto chunkData = ChunkUtils::InitializeData(_chunkSize);

		_generator->PaintChunk(chunkData, currentOrigin, _chunkSize);
		chunk->Load(chunkData);

		_loadedChunks.push_back(std::move(chunk));
	}
}

void ChunkManager::UpdateChunksContainer(const glm::ivec3 normalizedPosition)
{
	auto oldOrigins = _loadedChunksOrigin;
	_loadedChunksOrigin.clear();

	_log.Trace("Current chunk origin: " + 
			   std::to_string(normalizedPosition.x) + ", " + 
			   std::to_string(normalizedPosition.y) + ", " + 
			   std::to_string(normalizedPosition.z));

	const auto yBound = normalizedPosition.y + _renderDistance;
	for (auto y = -yBound; y <= yBound; ++y)
	{
		const auto xBound = _renderDistance - abs(y);
		for (auto x = -xBound; x <= xBound; ++x)
		{
			const auto zBound = abs(abs(x) + abs(y) - _renderDistance);
			for (auto z = -zBound; z <= zBound; ++z)
			{
				const auto origin = glm::ivec3(x + normalizedPosition.x,
											   y + normalizedPosition.y,
				                               z + normalizedPosition.z);

				_loadedChunksOrigin.emplace_back(origin);

				AddChunkToListIfIsNew(origin, oldOrigins);
			}
		}
	}

	RemoveExcludedChunks(oldOrigins);
}

ChunkManager::ChunkManager(const int chunkSize, const int renderDistance, Camera& camera)
	: _camera(camera), _renderDistance(renderDistance), _chunkSize(chunkSize)
{
	_chunksToRender = GetChunksToRenderCount();
	_lastChunkWithPlayer = GetNormalizedPosition(_camera.GetPosition());
}

void ChunkManager::Update()
{
	const auto currentChunkWithPlayer = GetNormalizedPosition(_camera.GetPosition());
	if (currentChunkWithPlayer != _lastChunkWithPlayer)
	{
		_lastChunkWithPlayer = currentChunkWithPlayer;
		UpdateChunksContainer(_lastChunkWithPlayer);
	}
	
	for (const auto& chunk : _loadedChunks)
	{
		chunk->Draw();
	}
}

void ChunkManager::Bind(const std::shared_ptr<WorldGenerator>& worldGenerator)
{
	if (!worldGenerator->IsInitialized())
	{
		throw std::logic_error("The world generator is not initialized!");
	}

	_generator = worldGenerator;
	
	UpdateChunksContainer(_lastChunkWithPlayer);
}

unsigned ChunkManager::GetChunksToRenderCount() const
{
	unsigned result = 0;
	for (auto i = 0; i < _renderDistance; ++i)
	{
		result += 2 * CountChunksRecursive(i);
	}

	return CountChunksRecursive(_renderDistance) + result; 
}

Camera& ChunkManager::GetCamera() const
{
	return _camera;
}

unsigned ChunkManager::GetChunkSize() const
{
	return _chunkSize;
}
