#include "Chunk.h"

void Chunk::DrawBlockIfExists(const int x, const int y, const int z) const
{
	if (_blocks[x][y][z] != nullptr && !_isDisabled[x][y][z])
	{
		_chunkManager.GetCamera().Add(*_blocks[x][y][z]);
		_blocks[x][y][z]->Draw();
	}
}

void Chunk::OptimizeCornersOnXY(const std::vector<float>& vector, const std::vector<float>& borderSurfaceMaxX,
	const std::vector<float>& borderSurfaceMinY, const std::vector<float>& borderSurfaceMaxY)
{
}

void Chunk::OptimizeCornersOnYZ(const std::vector<float>& vector, const std::vector<float>& borderSurfaceMaxY,
	const std::vector<float>& borderSurfaceMinZ, const std::vector<float>& borderSurfaceMaxZ)
{
}

void Chunk::OptimizeCornersOnXZ(const std::vector<float>& vector, const std::vector<float>& borderSurfaceMaxX,
	const std::vector<float>& borderSurfaceMinZ, const std::vector<float>& borderSurfaceMaxZ)
{
}

void Chunk::ResetCornersVisibility()
{
	constexpr auto end = chunk_size - 1;
	for (auto x = 0; x < chunk_size; ++x)
	{
		for (auto y = 0; y < chunk_size; ++y)
		{
			for (auto z = 0; z < chunk_size; ++z)
			{
				_isDisabled[x][ 0 ][ 0 ] = false;
				_isDisabled[x][end][ 0 ] = false;
				_isDisabled[x][ 0 ][end] = false;
				_isDisabled[x][end][end] = false;

				_isDisabled[ 0 ][y][ 0 ] = false;
				_isDisabled[end][y][ 0 ] = false;
				_isDisabled[ 0 ][y][end] = false;
				_isDisabled[end][y][end] = false;

				_isDisabled[ 0 ][ 0 ][z] = false;
				_isDisabled[end][ 0 ][z] = false;
				_isDisabled[ 0 ][end][z] = false;
				_isDisabled[end][end][z] = false;
			}
		}
	}
}

void Chunk::OptimizeBordersOnX(const std::vector<float>& borderSurfaceMinX, const std::vector<float>& borderSurfaceMaxX)
{
	auto index = 0;
	for (auto y = 0; y < chunk_size; ++y)
	{
		for (auto z = 0; z < chunk_size; ++z)
		{
			if (borderSurfaceMinX[index] <= 0)
			{
				_isDisabled[0][y][z] = true;
			}

			if (borderSurfaceMaxX[index] <= 0)
			{
				_isDisabled[chunk_size - 1][y][z] = true;
			}

			++index;
		}
	}
}

void Chunk::OptimizeBordersOnY(const std::vector<float>& borderSurfaceMinY, const std::vector<float>& borderSurfaceMaxY)
{
	auto index = 0;
	for (auto x = 0; x < chunk_size; ++x)
	{
		for (auto z = 0; z < chunk_size; ++z)
		{
			if (borderSurfaceMinY[index] <= 0)
			{
				_isDisabled[x][0][z] = true;
			}

			if (borderSurfaceMaxY[index] <= 0)
			{
				_isDisabled[x][chunk_size - 1][z] = true;
			}

			++index;
		}
	}
}

void Chunk::OptimizeBordersOnZ(const std::vector<float>& borderSurfaceMinZ, const std::vector<float>& borderSurfaceMaxZ)
{
	auto index = 0;
	for (auto x = 0; x < chunk_size; ++x)
	{
		for (auto y = 0; y < chunk_size; ++y)
		{
			if (borderSurfaceMinZ[index] <= 0)
			{
				_isDisabled[x][y][0] = true;
			}

			if (borderSurfaceMaxZ[index] <= 0)
			{
				_isDisabled[x][y][chunk_size - 1] = true;
			}

			++index;
		}
	}
}

Chunk::Chunk(const glm::vec3 origin, ChunkManager& chunkManager) : _chunkManager(chunkManager)
{
	_midPoint = static_cast<float>(chunk_size) / 2.0f;
	_midPoint += chunk_size % 2 == 0 ? 0.5f : 0.0f;

	_origin = origin * static_cast<float>(chunk_size);
}

void Chunk::Load(const std::vector<std::vector<std::vector<Block*>>>& blocks)
{
	std::move(blocks.begin(), blocks.end(), std::back_inserter(_blocks));
}

void Chunk::Optimize(const std::vector<float>& borderSurfaceMinX, const std::vector<float>& borderSurfaceMaxX,
					 const std::vector<float>& borderSurfaceMinY, const std::vector<float>& borderSurfaceMaxY,
					 const std::vector<float>& borderSurfaceMinZ, const std::vector<float>& borderSurfaceMaxZ)
{
	OptimizeBordersOnX(borderSurfaceMinX, borderSurfaceMaxX);
	OptimizeBordersOnY(borderSurfaceMinY, borderSurfaceMaxY);
	OptimizeBordersOnZ(borderSurfaceMinZ, borderSurfaceMaxZ);

	OptimizeCornersOnXY(borderSurfaceMinX, borderSurfaceMaxX, borderSurfaceMinY, borderSurfaceMaxY);
	OptimizeCornersOnYZ(borderSurfaceMinY, borderSurfaceMaxY, borderSurfaceMinZ, borderSurfaceMaxZ);
	OptimizeCornersOnXZ(borderSurfaceMinX, borderSurfaceMaxX, borderSurfaceMinZ, borderSurfaceMaxZ);

	for (auto x = 0; x < chunk_size; ++x)
	{
		for (auto y = 0; y < chunk_size; ++y)
		{
			for (auto z = 0; z < chunk_size; ++z)
			{
				DrawBlockIfExists(x, y, z);
			}
		}
	}
}

void Chunk::Draw() const
{
	for (auto x = 0; x < chunk_size; ++x)
	{
		for (auto y = 0; y < chunk_size; ++y)
		{
			for (auto z = 0; z < chunk_size; ++z)
			{
				DrawBlockIfExists(x, y, z);
			}
		}
	}
}

glm::vec3 Chunk::GetOrigin() const
{
	return _origin;
}

float Chunk::GetMidpoint() const
{
	return _midPoint;
}
