#pragma once
#include "Core/Metadata.h"
#include "Sandbox/Model/BlockModel.h"
#include "Sandbox/Model/Mesh/Geometry/Shader.h"

class BlocksProvider
{
	Metadata _blocksMetadata;
	Shader _blockShader = Shader("src/Data/Shaders/Block.vert", "src/Data/Shaders/Block.frag");

	std::array<std::vector<Vertex>, 6> _faceVertices
	{
		// Front
		std::vector<Vertex>
		{
			Vertex{0.0f, 0.0f, 0.0f},
			Vertex{1.0f, 0.0f, 0.0f},
			Vertex{1.0f, 1.0f, 0.0f},
			Vertex{0.0f, 1.0f, 0.0f},
		},

		// Back
		std::vector<Vertex>
		{
			Vertex{0.0f, 0.0f, 1.0f},
			Vertex{0.0f, 1.0f, 1.0f},
			Vertex{1.0f, 1.0f, 1.0f},
			Vertex{1.0f, 0.0f, 1.0f},
		},

		// Left
		std::vector<Vertex>
		{
			Vertex{0.0f, 0.0f, 0.0f},
			Vertex{0.0f, 1.0f, 0.0f},
			Vertex{0.0f, 1.0f, 1.0f},
			Vertex{0.0f, 0.0f, 1.0f},
		},

		// Right
		std::vector<Vertex>
		{
			Vertex{1.0f, 0.0f, 0.0f},
			Vertex{1.0f, 0.0f, 1.0f},
			Vertex{1.0f, 1.0f, 1.0f},
			Vertex{1.0f, 1.0f, 0.0f},
		},

		// Top
		std::vector<Vertex>
		{
			Vertex{0.0f, 1.0f, 0.0f},
			Vertex{1.0f, 1.0f, 0.0f},
			Vertex{1.0f, 1.0f, 1.0f},
			Vertex{0.0f, 1.0f, 1.0f}
		},

		// Bottom
		std::vector<Vertex>
		{
			Vertex{0.0f, 0.0f, 0.0f},
			Vertex{0.0f, 0.0f, 1.0f},
			Vertex{1.0f, 0.0f, 1.0f},
			Vertex{1.0f, 0.0f, 0.0f}
		},
	};

	std::vector<Point> _faceIndices
	{
		Point{},
		Point{}
	};

	struct BlockFaceMesh
	{
		std::shared_ptr<Mesh> front  = std::make_shared<Mesh>(_faceVertices[0], _blockShader);
		std::shared_ptr<Mesh> back   = std::make_shared<Mesh>(_faceVertices[1], _blockShader);
		std::shared_ptr<Mesh> left   = std::make_shared<Mesh>(_faceVertices[2], _blockShader);
		std::shared_ptr<Mesh> right  = std::make_shared<Mesh>(_faceVertices[3], _blockShader);
		std::shared_ptr<Mesh> top    = std::make_shared<Mesh>(_faceVertices[4], _blockShader);
		std::shared_ptr<Mesh> bottom = std::make_shared<Mesh>(_faceVertices[5], _blockShader);
	};

public:
	explicit BlocksProvider(const std::string& filenameWithBlocksData);

	std::map<std::string, std::unique_ptr<BlockModel>> GetBlocks(const std::vector<std::string>& blocksTextureNames, const std::string& blocksSetName = "default");
};

