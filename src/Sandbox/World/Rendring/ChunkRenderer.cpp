#include "ChunkRenderer.h"

#include "Core/EngineExceptions.h"
#include "Sandbox/Utils/Chunk/ChunkUtils.h"

std::vector<glm::ivec3> ChunkRenderer::Subtract(const std::vector<glm::ivec3>& aSet, const std::vector<glm::ivec3>& bSet)
{
	std::vector<glm::ivec3> result;

	for (const auto& value : aSet)
	{
		if (std::find(bSet.begin(), bSet.end(), value) == bSet.end())
		{
			result.emplace_back(value);
		}
	}

	return result;
}

glm::ivec3 ChunkRenderer::GetNormalizedPosition(glm::vec3 position) const
{
	position /= _renderView->GetChunkSize();
	position -= 0.5f;
	
	return {
		static_cast<int>(ceil(position.x)),
		static_cast<int>(ceil(position.y)),
		static_cast<int>(ceil(position.z))
	};
}

std::string ChunkRenderer::PositionToString(const glm::ivec3& position) const
{
	return std::to_string(position.x) + ", " + 
		   std::to_string(position.y) + ", " + 
		   std::to_string(position.z);
}

void ChunkRenderer::RemoveChunkAt(const glm::ivec3& origin)
{
	const auto outdatedChunk = 
		std::find_if(
			_loadedChunks.begin(), 
			_loadedChunks.end(),
		    [&](const std::unique_ptr<Chunk>& chunk)
		    {
		        return chunk->GetOrigin() == origin;
		    }
	);

	if (outdatedChunk == _loadedChunks.end())
	{
		throw NotFoundException("The chunk with given origin is not loaded!");
	}

	_log.Trace("Removed chunk: " + PositionToString(origin));
	_loadedChunks.erase(outdatedChunk);
}

void ChunkRenderer::SpawnChunkAt(const glm::ivec3& origin)
{
	_log.Trace("Added chunk: " + PositionToString(origin));
	
	const auto chunkFrame = ChunkFrame{origin, _renderView->GetChunkSize()};
	auto chunkBlocks	  = ChunkUtils::InitializeData(_renderView->GetChunkSize());
	_generator.PaintChunk(chunkFrame, chunkBlocks);

	auto chunk = std::make_unique<Chunk>(chunkFrame, std::move(chunkBlocks), _camera);
	_loadedChunks.emplace_back(std::move(chunk));
}

void ChunkRenderer::RenderChunksAround(const glm::ivec3& normalizedOrigin)
{
	const auto previousChunksAroundOrigins = _loadedChunksOrigins;
	const auto currentChunksAroundOrigins = _renderView->GetChunksAround(normalizedOrigin);

	const auto newChunksOrigins = Subtract(currentChunksAroundOrigins, previousChunksAroundOrigins);
	const auto outdatedChunksOrigins = Subtract(previousChunksAroundOrigins, currentChunksAroundOrigins);

	for (const auto& outdatedOrigin : outdatedChunksOrigins)
	{
		RemoveChunkAt(outdatedOrigin);
	}

	for (const auto& newOrigin : newChunksOrigins)
	{
		SpawnChunkAt(newOrigin);
	}

	_loadedChunksOrigins = currentChunksAroundOrigins;
}

ChunkRenderer::ChunkRenderer(WorldGenerator& generator, std::unique_ptr<RenderView>& renderView, Camera& camera)
	: _camera(camera), _renderView(std::move(renderView)), _generator(generator), _previousNormalizedPosition(GetNormalizedPosition(camera.GetPosition()))
{
	RenderChunksAround(_previousNormalizedPosition);
}

void ChunkRenderer::Render()
{
	const auto currentNormalizedPosition = GetNormalizedPosition(_camera.GetPosition());

	if (currentNormalizedPosition != _previousNormalizedPosition)
	{
		_previousNormalizedPosition = currentNormalizedPosition;
		RenderChunksAround(currentNormalizedPosition);
	}

	for (const auto& chunk : _loadedChunks)
	{
		chunk->Draw();
	}
}

void ChunkRenderer::SetRenderView(std::unique_ptr<RenderView>& renderView)
{
	_renderView = std::move(renderView);
}
