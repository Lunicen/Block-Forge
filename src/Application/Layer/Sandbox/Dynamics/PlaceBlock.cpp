#include "PlaceBlock.h"
#include "Application/Layer/Sandbox/World/Chunks/ChunkUtils.h"




void PlaceBlock::Place(glm::vec3 _orientation, glm::vec3 _position, std::unordered_map<Position, std::unique_ptr<Chunk>>& chunks, BlockMap& blockMap)
{
	size_t chunkSize = 16; //get from SandboxLayer.h
	int maxRadiusCoefficient = 4;

	for(int radiusCoefficient = 0; radiusCoefficient < maxRadiusCoefficient; radiusCoefficient++)
	{
		glm::vec3 pos = _position + _orientation * float(radiusCoefficient);
		pos.x = float(int(pos.x));
		pos.y = float(int(pos.y));
		pos.z = float(int(pos.z));

		auto chunkPosition = ChunkUtils::GetNormalizedPosition(pos, chunkSize);

		pos.x = float(int(pos.x) % chunkSize);
		pos.y = float(int(pos.y) % chunkSize);
		pos.z = float(int(pos.z) % chunkSize);

		if (chunks.find(chunkPosition) != chunks.end())
		{
			auto blocksInChunk = chunks.at(chunkPosition)->GetBlocks();
			if ((blocksInChunk.at(ChunkUtils::GetBlockIndex(pos, chunkSize)).blockFlags & 0b00000010) == 0)
			{
				continue;
			}

			pos += glm::vec3(0, 1, 0);
		//	chunkPosition = ChunkUtils::GetNormalizedPosition(pos, chunkSize);

			auto newBlock = blocksInChunk.at(ChunkUtils::GetBlockIndex(pos, chunkSize));
			newBlock.blockModel = blockMap.GetId("dirt2");

			newBlock.blockFlags |= 0b11111110;

			blocksInChunk.at(ChunkUtils::GetBlockIndex(Position(pos), chunkSize)) = newBlock;
			chunks.at(chunkPosition)->LoadBlocksAndBuildMesh(blocksInChunk, ChunkFrame{ chunkPosition, chunkSize }, blockMap);
			break;
		}
	}
}

