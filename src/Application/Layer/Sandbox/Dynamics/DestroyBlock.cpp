#include "DestroyBlock.h"

#include "Application/Layer/Sandbox/World/Chunks/Structure/Chunk.h"
#include "Application/Layer/Sandbox/World/Chunks/Structure/ChunkFrame.h"

void DestroyBlock::FindBlock()
{



}
 void DestroyBlock::Destroy(glm::vec3 _orientation, glm::vec3 _position, std::unordered_map<Position, std::unique_ptr<Chunk>>& chunks, BlockMap& blockMap)
{

	 size_t chunkSize = 16; //get from SandboxLayer.h
	 int maxRadiusCoefficient = 4;

	 for (int radiusCoefficient = 1; radiusCoefficient < maxRadiusCoefficient; radiusCoefficient++)
	 {
		 glm::vec3 pos = _position + _orientation * float(radiusCoefficient);

		 auto chunkPosition = ChunkUtils::GetNormalizedPosition(pos, chunkSize);
		 if (chunks.find(chunkPosition) != chunks.end())
		 {


			 auto blocksInChunk = chunks.at(chunkPosition)->GetBlocks();
			 if ((blocksInChunk.at(ChunkUtils::GetBlockIndex(pos, chunkSize)).blockFlags & 0b00000010) == 0)
			 {
				 continue;
			 }


			 auto newBlock = blocksInChunk.at(ChunkUtils::GetBlockIndex(pos, chunkSize));
			 newBlock.blockFlags = 0b00000000;

			 blocksInChunk.at(ChunkUtils::GetBlockIndex(pos-glm::vec3(1,0,0), chunkSize)).blockFlags |=  0b11111100;
;
			 blocksInChunk.at(ChunkUtils::GetBlockIndex(pos + glm::vec3(1, 0, 0), chunkSize)).blockFlags |= 0b11111100;
			 blocksInChunk.at(ChunkUtils::GetBlockIndex(pos - glm::vec3(0, 1, 0), chunkSize)).blockFlags |= 0b11111100;
			 blocksInChunk.at(ChunkUtils::GetBlockIndex(pos + glm::vec3(0, 1, 0), chunkSize)).blockFlags |= 0b11111100;
			 blocksInChunk.at(ChunkUtils::GetBlockIndex(pos - glm::vec3(0, 0, 1), chunkSize)).blockFlags |= 0b11111100;
			 blocksInChunk.at(ChunkUtils::GetBlockIndex(pos + glm::vec3(0, 0, 1), chunkSize)).blockFlags |= 0b11111100;




			 blocksInChunk.at(ChunkUtils::GetBlockIndex(Position(pos), chunkSize)) = newBlock;
			 chunks.at(chunkPosition)->LoadBlocksAndBuildMesh(blocksInChunk, ChunkFrame{ chunkPosition, chunkSize }, blockMap);
			 break;
		 }
	 }






}
