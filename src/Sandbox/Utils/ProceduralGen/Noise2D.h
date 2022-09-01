#pragma once
#include "Noise.h"
#include "Sandbox/Utils/Chunk/ChunkFrame.h"

class Noise2D : protected Noise
{
	static std::vector<std::vector<float>> ConvertNoiseFrom1DTo2D(const std::vector<float>& noise, const size_t& size);
	
public:

	/// @brief The constructor.
	///	@param encodedTree - A string with encoded tree generated by using FastNoise2 tool.
	///	@param seed - noise seed for different results.
	///	@param frequency - The frequency of the encoded noise function.
	Noise2D(const std::string& encodedTree, const int seed, const float frequency)
		: Noise(encodedTree, seed, frequency)
	{
	}

	/// @brief Get noise that is at certain point on the map.
	/// @param frame - the frame of the chunk.
	/// @param xOffset - offset from origin the X axis. 
	///	@param yOffset - offset from origin the Y axis. 
	float GetNoiseAt(const ChunkFrame& frame, int xOffset, int yOffset) const;

	std::vector<std::vector<float>> GetNoise(const ChunkFrame& frame, int xOffset, int yOffset, int expansionFactor = 0) const;

	/// @brief Get noise of the chunk at certain position on the map.
	/// @param frame - frame of the chunk.
	/// @param expansionFactor - the factor that expands or shrinks the dimensions of the chunk.
	std::vector<std::vector<float>> GetNoise(const ChunkFrame& frame, int expansionFactor = 0) const;
};

