#include "PlaceBlock.h"
#include "Application/Layer/Sandbox/World/Chunks/ChunkUtils.h"




void PlaceBlock::Place(glm::vec3 _orientation, glm::vec3 _position, std::unordered_map<Position, std::unique_ptr<Chunk>>& chunks, BlockMap& blockMap)
{
	constexpr int maxRadiusCoefficient = 4;

	for(int radiusCoefficient = 0; radiusCoefficient < maxRadiusCoefficient; radiusCoefficient++)
	{
		size_t chunkSize = 16;
		glm::vec3 pos = _position + _orientation * static_cast<float>(radiusCoefficient);
		pos.x = static_cast<float>(static_cast<int>(pos.x));
		pos.y = static_cast<float>(static_cast<int>(pos.y));
		pos.z = static_cast<float>(static_cast<int>(pos.z));

		auto chunkPosition = ChunkUtils::GetNormalizedPosition(pos, chunkSize);
		const auto chunkPositionForNewBlock = ChunkUtils::GetNormalizedPosition(pos + glm::vec3(0, 1, 0), chunkSize);

		pos.x = static_cast<float>(static_cast<int>(pos.x) % chunkSize);
		pos.y = static_cast<float>(static_cast<int>(pos.y) % chunkSize);
		pos.z = static_cast<float>(static_cast<int>(pos.z) % chunkSize);

		if (chunks.find(chunkPosition) != chunks.end())
		{
			auto blocksInChunk = chunks.at(chunkPosition)->GetBlocks();
			if ((blocksInChunk.at(ChunkUtils::GetBlockIndex(pos, chunkSize)).blockFlags & 0b00000010) == 0)
			{
				continue;
			}

			pos += glm::vec3(0, 1, 0);
			auto newBlock = blocksInChunk.at(ChunkUtils::GetBlockIndex(pos, chunkSize));
			newBlock.blockModel = blockMap.GetId("dirt2");

			newBlock.blockFlags |= 0b11111110;

			blocksInChunk.at(ChunkUtils::GetBlockIndex(Position(pos), chunkSize)) = newBlock;
			chunks.at(chunkPositionForNewBlock)->LoadBlocksAndBuildMesh(blocksInChunk, ChunkFrame{ chunkPositionForNewBlock, chunkSize }, blockMap);
			break;
		}
	}
}

