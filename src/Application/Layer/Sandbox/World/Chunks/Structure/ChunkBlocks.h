#pragma once
// ReSharper disable once CppUnusedIncludeDirective
#include <vector>

#include "Application/Layer/Sandbox/Model/BlockModel.h"

/// @brief This struct represents the block data flags
///	in a human readable format.
struct BlockFlags
{
	/// @brief Front face visibility flag.
	Byte frontFace  = 0b10000000;
	/// @brief Back face visibility flag.
	Byte backFace   = 0b01000000;
	/// @brief Left face visibility flag. 
	Byte leftFace   = 0b00100000;
	/// @brief Right face visibility flag. 
	Byte rightFace  = 0b00010000;
	/// @brief Top face visibility flag. 
	Byte topFace    = 0b00001000;
	/// @brief Bottom face visibility flag. 
	Byte bottomFace = 0b00000100; 

	/// @brief "Is block active?" flag (or is it air?)
	Byte activate   = 0b00000010;
};
const BlockFlags BlockFlag;

/// @brief Contains the information about a certain block and the visibility of its faces.
struct BlockData
{
	/// @brief Block ID from the blocks map.
	Byte blockModel = 0b00000000;

	/// @brief Represents the flags of of the block.
	///	@details
	/// What each bit means: <br>
	/// 0: Is the FRONT face of this block visible?, <br>
	///	1: Is the BACK face of this block visible?, <br>
	///	2: Is the LEFT face of this block visible?, <br>
	///	3: Is the RIGHT face of this block visible?, <br>
	///	4: Is the TOP face of this block visible?, <br>
	///	5: Is the BOTTOM face of this block visible?, <br>
	///	6: Is the block active? Or it's treated as an air. <br>
	///	7: unused.
	Byte blockFlags = 0b00000000;
};

template <>
/// @brief A custom defined hash operator for the Position type variable.
///	@details This hash operator overload allows to use the 3d vector
///	as a key in the map.
struct std::hash<Position>
{
	/// @brief Definition of how to handle the passed origin as a key in the map.
    size_t operator()(const Position& origin) const noexcept
    {
        return std::hash<std::string>()
    	(
			std::to_string(origin.x) + "." +
			std::to_string(origin.y) + "." + 
			std::to_string(origin.z)
		);
    }
};

/// @brief A structure that represents the body of typical chunk. Blocks and their visibility.
///	@details This map contains all blocks that are included in the chunk
///	and maps the location of the block as a key, and it's model and
///	faces visibility as a key.
using ChunkBlocks = std::vector<BlockData>;
