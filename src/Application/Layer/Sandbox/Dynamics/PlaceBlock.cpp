#include "PlaceBlock.h"
#include "Application/Layer/Sandbox/World/Chunks/ChunkUtils.h"

void PlaceBlock::Place(glm::vec3 orientation, glm::vec3 position, HashMap<Position, std::unique_ptr<Chunk>>& chunks, BlockMap& blockMap, const std::string& heldItem)
{
	constexpr int maxRadiusCoefficient = 4;

	for(int radiusCoefficient = 0; radiusCoefficient < maxRadiusCoefficient; radiusCoefficient++)
	{
		size_t chunkSize = 16;
		glm::vec3 pos = position + orientation* static_cast<float>(radiusCoefficient);
		pos.x = static_cast<float>(static_cast<int>(pos.x));
		pos.y = static_cast<float>(static_cast<int>(pos.y));
		pos.z = static_cast<float>(static_cast<int>(pos.z));

		auto chunkPosition = ChunkUtils::GetNormalizedPosition(pos, chunkSize);
		const auto chunkPositionForNewBlock = ChunkUtils::GetNormalizedPosition(pos + glm::vec3(0, 1, 0), chunkSize);

		pos.x = static_cast<float>(static_cast<int>(pos.x) % chunkSize);
		pos.y = static_cast<float>(static_cast<int>(pos.y) % chunkSize);
		pos.z = static_cast<float>(static_cast<int>(pos.z) % chunkSize);

		auto isThereBlock = 0b00000010;
		auto placeBlock = 0b11111110;
		if (chunks.find(chunkPosition) != chunks.end())
		{

			if (placeBlockOnChunk(chunks, chunkPosition, pos, chunkSize, isThereBlock, chunkPositionForNewBlock, blockMap, heldItem, placeBlock))
				break;
			continue;
		}
	}
}
bool PlaceBlock::placeBlockOnChunk(HashMap<Position, std::unique_ptr<Chunk>>& chunks, Position chunkPosition, glm::vec3& pos, size_t chunkSize,
	int isThereBlock, Position chunkPositionForNewBlock, BlockMap& blockMap, const std::string& heldItem , int placeBlock)
{
	auto blocksInChunk = chunks.at(chunkPosition)->GetBlocks();
	if ((blocksInChunk.at(ChunkUtils::GetBlockIndex(pos, chunkSize)).blockFlags & isThereBlock) == 0)
	{
		return false;
	}

	pos += glm::vec3(0, 1, 0);

	if (chunkPositionForNewBlock != chunkPosition) {
		blocksInChunk = chunks.at(chunkPositionForNewBlock)->GetBlocks();
		if (static_cast<int>(pos.x) == static_cast<int>(chunkSize))
			pos.x = 0;
		if (static_cast<int>(pos.y) == static_cast<int>(chunkSize))
			pos.y = 0;
		if (static_cast<int>(pos.z) == static_cast<int>(chunkSize))
			pos.z = 0;
	}
	if ((blocksInChunk.at(ChunkUtils::GetBlockIndex(pos, chunkSize)).blockFlags & isThereBlock) != 0)
	{
		return false;
	}
	auto newBlock = blocksInChunk.at(ChunkUtils::GetBlockIndex(pos, chunkSize));


	newBlock.blockModel = blockMap.GetId(heldItem);

	newBlock.blockFlags |= placeBlock;

	blocksInChunk.at(ChunkUtils::GetBlockIndex(Position(pos), chunkSize)) = newBlock;
	chunks.at(chunkPositionForNewBlock)->LoadBlocksAndBuildMesh(blocksInChunk, ChunkFrame{ chunkPositionForNewBlock, chunkSize }, blockMap);
	return true;
}
