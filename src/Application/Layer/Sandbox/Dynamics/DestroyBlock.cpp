#include "DestroyBlock.h"
#include "Application/Layer/Sandbox/World/Chunks/Structure/Chunk.h"
#include "Application/Layer/Sandbox/World/Chunks/Structure/ChunkFrame.h"

 void DestroyBlock::Destroy(glm::vec3 _orientation, glm::vec3 _position, std::unordered_map<Position, std::unique_ptr<Chunk>>& chunks, BlockMap& blockMap)
{
	constexpr int maxRadiusCoefficient = 4;

	 for (int radiusCoefficient = 0; radiusCoefficient < maxRadiusCoefficient; radiusCoefficient++)
	 {
		 size_t chunkSize = 16;
		 glm::vec3 pos = _position + _orientation * static_cast<float>(radiusCoefficient);
		 pos.x = static_cast<float>(static_cast<int>(pos.x));
		 pos.y = static_cast<float>(static_cast<int>(pos.y));
		 pos.z = static_cast<float>(static_cast<int>(pos.z));

		 glm::vec3 position = _position;
		 position.x = static_cast<float>(static_cast<int>(pos.x));
		 position.y = static_cast<float>(static_cast<int>(pos.y));
		 position.z = static_cast<float>(static_cast<int>(pos.z));

		 auto chunkPosition = ChunkUtils::GetNormalizedPosition(pos, chunkSize);

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
		 	 auto newBlock = blocksInChunk.at(ChunkUtils::GetBlockIndex(pos, chunkSize));
			 newBlock.blockFlags = 0b00000000;

			
		 	 if (static_cast<int>(pos.x) % chunkSize == 0)
			 {
				 blocksInChunk.at(ChunkUtils::GetBlockIndex(pos + glm::vec3(1, 0, 0), chunkSize)).blockFlags |= 0b11111100;

				 auto chunkPosition2 = ChunkUtils::GetNormalizedPosition(position - glm::vec3(1,0,0), chunkSize);
				 auto blocksInChunk2 = chunks.at(chunkPosition2)->GetBlocks();
		 	 	 blocksInChunk2.at(ChunkUtils::GetBlockIndex(pos + glm::vec3(chunkSize-1, 0, 0), chunkSize)).blockFlags |= 0b11111100;
				 chunks.at(chunkPosition2)->LoadBlocksAndBuildMesh(blocksInChunk2, ChunkFrame{ chunkPosition2, chunkSize }, blockMap);
			 }
			 else if (static_cast<int>(pos.x) % chunkSize == chunkSize-1)
			 {
			 	blocksInChunk.at(ChunkUtils::GetBlockIndex(pos - glm::vec3(1, 0, 0), chunkSize)).blockFlags |= 0b11111100;

				auto chunkPosition2 = ChunkUtils::GetNormalizedPosition(position + glm::vec3(1, 0, 0), chunkSize);
				auto blocksInChunk2 = chunks.at(chunkPosition2)->GetBlocks();
				blocksInChunk2.at(ChunkUtils::GetBlockIndex(pos - glm::vec3(chunkSize-1, 0, 0), chunkSize)).blockFlags |= 0b11111100;
				chunks.at(chunkPosition2)->LoadBlocksAndBuildMesh(blocksInChunk2, ChunkFrame{ chunkPosition2, chunkSize }, blockMap);

			 }
			 else{ 
				 blocksInChunk.at(ChunkUtils::GetBlockIndex(pos - glm::vec3(1, 0, 0), chunkSize)).blockFlags |= 0b11111100;
				 blocksInChunk.at(ChunkUtils::GetBlockIndex(pos + glm::vec3(1, 0, 0), chunkSize)).blockFlags |= 0b11111100;
			 }

			 if (static_cast<int>(pos.y) % chunkSize == 0)
			 {
				 blocksInChunk.at(ChunkUtils::GetBlockIndex(pos + glm::vec3(0, 1, 0), chunkSize)).blockFlags |= 0b11111100;

				 auto chunkPosition2 = ChunkUtils::GetNormalizedPosition(position - glm::vec3(0, 1, 0), chunkSize);
				 auto blocksInChunk2 = chunks.at(chunkPosition2)->GetBlocks();
				 blocksInChunk2.at(ChunkUtils::GetBlockIndex(pos + glm::vec3(0, chunkSize-1, 0), chunkSize)).blockFlags |= 0b11111100;
				 chunks.at(chunkPosition2)->LoadBlocksAndBuildMesh(blocksInChunk2, ChunkFrame{ chunkPosition2, chunkSize }, blockMap);

			 }
			 else if (static_cast<int>(pos.y) % chunkSize == chunkSize - 1)
			 {
				 blocksInChunk.at(ChunkUtils::GetBlockIndex(pos - glm::vec3(0, 1, 0), chunkSize)).blockFlags |= 0b11111100;

				 auto chunkPosition2 = ChunkUtils::GetNormalizedPosition(position + glm::vec3(0, 1, 0), chunkSize);
				 auto blocksInChunk2 = chunks.at(chunkPosition2)->GetBlocks();
				 blocksInChunk2.at(ChunkUtils::GetBlockIndex(pos - glm::vec3(0, chunkSize-1, 0), chunkSize)).blockFlags |= 0b11111100;
				 chunks.at(chunkPosition2)->LoadBlocksAndBuildMesh(blocksInChunk2, ChunkFrame{ chunkPosition2, chunkSize }, blockMap);

			 }
			 else {
				 blocksInChunk.at(ChunkUtils::GetBlockIndex(pos - glm::vec3(0, 1, 0), chunkSize)).blockFlags |= 0b11111100;
				 blocksInChunk.at(ChunkUtils::GetBlockIndex(pos + glm::vec3(0 , 1, 0), chunkSize)).blockFlags |= 0b11111100;
			 }

			 if (static_cast<int>(pos.z) % chunkSize == 0)
			 {
				 blocksInChunk.at(ChunkUtils::GetBlockIndex(pos + glm::vec3(0, 0, 1), chunkSize)).blockFlags |= 0b11111100;
				 auto chunkPosition2 = ChunkUtils::GetNormalizedPosition(position - glm::vec3(0, 0, 1), chunkSize);
				 auto blocksInChunk2 = chunks.at(chunkPosition2)->GetBlocks();
				 blocksInChunk2.at(ChunkUtils::GetBlockIndex(pos + glm::vec3(0, 0, chunkSize-1), chunkSize)).blockFlags |= 0b11111100;
				 chunks.at(chunkPosition2)->LoadBlocksAndBuildMesh(blocksInChunk2, ChunkFrame{ chunkPosition2, chunkSize }, blockMap);

			 }
			 else if (static_cast<int>(pos.z) % chunkSize == chunkSize - 1)
			 {
				 blocksInChunk.at(ChunkUtils::GetBlockIndex(pos - glm::vec3(0, 0, 1), chunkSize)).blockFlags |= 0b11111100;

				 auto chunkPosition2 = ChunkUtils::GetNormalizedPosition(position + glm::vec3(0, 0, 1), chunkSize);
				 auto blocksInChunk2 = chunks.at(chunkPosition2)->GetBlocks();
				 blocksInChunk2.at(ChunkUtils::GetBlockIndex(pos- glm::vec3(0, 0, chunkSize-1), chunkSize)).blockFlags |= 0b11111100;
				 chunks.at(chunkPosition2)->LoadBlocksAndBuildMesh(blocksInChunk2, ChunkFrame{ chunkPosition2, chunkSize }, blockMap);

			 }
			 else {
				 blocksInChunk.at(ChunkUtils::GetBlockIndex(pos - glm::vec3(0, 0, 1), chunkSize)).blockFlags |= 0b11111100;
				 blocksInChunk.at(ChunkUtils::GetBlockIndex(pos + glm::vec3(0, 0, 1), chunkSize)).blockFlags |= 0b11111100;
			 }

			 blocksInChunk.at(ChunkUtils::GetBlockIndex(Position(pos), chunkSize)) = newBlock;
			 chunks.at(chunkPosition)->LoadBlocksAndBuildMesh(blocksInChunk, ChunkFrame{ chunkPosition, chunkSize }, blockMap);
			 break;
		 }
	 }






}
