#include "ChunkManager.h"

#include "Sandbox/Utils/EngineExceptions.h"
#include "Sandbox/Utils/Chunk/ChunkUtils.h"

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

size_t ChunkManager::CountChunksRecursive(const size_t level)
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
				return chunk->GetOrigin() == oldOrigin * static_cast<int>(_chunkSize);
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

ChunkFrame ChunkManager::CreateChunkFrame(const glm::ivec3& origin) const
{
	return ChunkFrame{origin, _chunkSize};
}

ChunkBlocks ChunkManager::CreateChunkBlocks() const
{
	return ChunkUtils::InitializeData(_chunkSize);
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

		const auto chunkFrame = CreateChunkFrame(currentOrigin);
		auto chunkData = CreateChunkBlocks();
		
		_generator->PaintChunk(chunkFrame, chunkData);
		chunk->Load(chunkData);

		_loadedChunks.push_back(std::move(chunk));
	}
}

void ChunkManager::UpdateChunksContainer(const glm::ivec3 normalizedPosition)
{
	const auto oldOrigins = _loadedChunksOrigin;
	_loadedChunksOrigin.clear();

	_log.Trace("Current chunk origin: " + 
			   std::to_string(normalizedPosition.x) + ", " + 
			   std::to_string(normalizedPosition.y) + ", " + 
			   std::to_string(normalizedPosition.z));

	const auto yBound = static_cast<int>(_renderDistance);

	for (auto y = -yBound; y <= yBound; ++y)
	{
		const auto xBound = yBound - abs(y);

		for (auto x = -xBound; x <= xBound; ++x)
		{
			const auto zBound = abs(abs(x) + abs(y) - yBound);
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
	_generator = worldGenerator;

	UpdateChunksContainer(_lastChunkWithPlayer);
}

size_t ChunkManager::GetChunksToRenderCount() const
{
	size_t result = 0;
	for (size_t i = 0; i < _renderDistance; ++i)
	{
		result += 2 * CountChunksRecursive(i);
	}

	return CountChunksRecursive(_renderDistance) + result; 
}

Camera& ChunkManager::GetCamera() const
{
	return _camera;
}

size_t ChunkManager::GetChunkSize() const
{
	return _chunkSize;
}
