#include "DestroyBlock.h"

#include "Application/Layer/Sandbox/World/Chunks/Structure/Chunk.h"
#include "Application/Layer/Sandbox/World/Chunks/Structure/ChunkFrame.h"

void DestroyBlock::FindBlock()
{



}
 void DestroyBlock::Destroy(glm::vec3 _orientation, glm::vec3 _position, std::unordered_map<Position, std::unique_ptr<Chunk>>& chunks, BlockMap& blockMap)
{

	 

		 if (chunks.find(Position(0, 0, 0)) != chunks.end())
		 {
			 auto blocksInChunk = chunks.at(Position(0, 0, 0))->GetBlocks();
			 size_t chunkSize = 16; //get from SandboxLayer.h

			 auto newBlock = blocksInChunk.at(ChunkUtils::GetBlockIndex(Position(0, 0, 0), chunkSize));
			 newBlock.blockModel = blockMap.GetId("dirt2");

			 newBlock.blockFlags = 0b11111101;
			 

			 blocksInChunk.at(ChunkUtils::GetBlockIndex(Position(0, 0, 0), chunkSize)) = newBlock;
			 chunks.at(Position(0, 0, 0))->LoadBlocksAndBuildMesh(blocksInChunk, ChunkFrame{ Position{0,0,0}, chunkSize }, blockMap);
		 }










}
