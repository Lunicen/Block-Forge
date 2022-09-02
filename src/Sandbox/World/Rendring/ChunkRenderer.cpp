#include "ChunkRenderer.h"

#include "Sandbox/Utils/Chunk/ChunkUtils.h"

std::string ChunkRenderer::PositionToString(const glm::ivec3& position) const
{
	return std::to_string(position.x) + ", " + 
		   std::to_string(position.y) + ", " + 
		   std::to_string(position.z);
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

void ChunkRenderer::AddChunkToList(const glm::ivec3& origin)
{
	_log.Trace("Added chunk: " + PositionToString(origin));
	
	const auto chunkFrame = ChunkFrame{origin, _renderView->GetChunkSize()};
	auto chunkBlocks	  = ChunkUtils::InitializeData(_renderView->GetChunkSize());
	_generator.PaintChunk(chunkFrame, chunkBlocks);

	auto chunk = std::make_unique<Chunk>(chunkFrame, std::move(chunkBlocks), _camera);
	_loadedChunks.emplace_back(std::move(chunk));
}

void ChunkRenderer::AddOnlyNewChunks(const std::vector<glm::ivec3>& currentOrigins, const std::vector<glm::ivec3>& previousOrigins)
{
	for (const auto& currentOrigin : currentOrigins)
	{
		if (std::find(previousOrigins.begin(), previousOrigins.end(), currentOrigin) == previousOrigins.end())
		{
			AddChunkToList(currentOrigin);
		}
	}
}

void ChunkRenderer::RemoveExcludedChunks(const std::vector<glm::ivec3>& oldOrigins)
{
	for (const auto& oldOrigin : oldOrigins)
	{
		if (std::find(_loadedChunksOrigins.begin(), _loadedChunksOrigins.end(), oldOrigin) != _loadedChunksOrigins.end())
		{
			_log.Trace("Reusing chunk: " + PositionToString(oldOrigin));
			continue;
		}

		auto outdatedChunk = std::find_if(_loadedChunks.begin(), _loadedChunks.end(),
			[&](const std::unique_ptr<Chunk>& chunk)
			{
				return chunk->GetOrigin() == oldOrigin * static_cast<int>(_renderView->GetChunkSize());
			}
		);

		if (outdatedChunk != _loadedChunks.end())
		{
			_log.Trace("Removed chunk: " + PositionToString(oldOrigin));
			_loadedChunks.erase(outdatedChunk);
		}
	}
}

void ChunkRenderer::RenderChunksAround(const glm::ivec3& normalizedOrigin)
{
	const auto& previousChunksAroundOrigins = _loadedChunksOrigins;
	const auto& currentChunksAroundOrigins = _renderView->GetChunksAround(normalizedOrigin);

	_loadedChunksOrigins.clear();

	AddOnlyNewChunks(currentChunksAroundOrigins, previousChunksAroundOrigins);
	RemoveExcludedChunks(previousChunksAroundOrigins);
}

ChunkRenderer::ChunkRenderer(WorldGenerator& generator, std::unique_ptr<RenderView>& renderView, Camera& camera)
	: _camera(camera), _renderView(std::move(renderView)), _generator(generator), _previousNormalizedPosition(GetNormalizedPosition(camera.GetPosition()))
{
}

void ChunkRenderer::Update()
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
