#pragma once
#include "Core/Metadata.h"
#include "Sandbox/Model/BlockModel.h"
#include "Sandbox/Model/Mesh/Geometry/Shader.h"

class BlockBuilder
{
	struct FaceVertices
	{
		std::vector<Vertex> front
		{
			Vertex{0.0f, 0.0f, 0.0f},
			Vertex{1.0f, 0.0f, 0.0f},
			Vertex{1.0f, 1.0f, 0.0f},
			Vertex{0.0f, 1.0f, 0.0f},
		};

		std::vector<Vertex> back
		{
			Vertex{0.0f, 0.0f, 1.0f},
			Vertex{0.0f, 1.0f, 1.0f},
			Vertex{1.0f, 1.0f, 1.0f},
			Vertex{1.0f, 0.0f, 1.0f},
		};
		
		std::vector<Vertex> left
		{
			Vertex{0.0f, 0.0f, 0.0f},
			Vertex{0.0f, 1.0f, 0.0f},
			Vertex{0.0f, 1.0f, 1.0f},
			Vertex{0.0f, 0.0f, 1.0f},
		};

		std::vector<Vertex> right
		{
			Vertex{1.0f, 0.0f, 0.0f},
			Vertex{1.0f, 0.0f, 1.0f},
			Vertex{1.0f, 1.0f, 1.0f},
			Vertex{1.0f, 1.0f, 0.0f},
		};
		
		std::vector<Vertex> top
		{
			Vertex{0.0f, 1.0f, 0.0f},
			Vertex{1.0f, 1.0f, 0.0f},
			Vertex{1.0f, 1.0f, 1.0f},
			Vertex{0.0f, 1.0f, 1.0f}
		};
		
		std::vector<Vertex> bottom
		{
			Vertex{0.0f, 0.0f, 0.0f},
			Vertex{0.0f, 0.0f, 1.0f},
			Vertex{1.0f, 0.0f, 1.0f},
			Vertex{1.0f, 0.0f, 0.0f}
		};
	} _faceVertices;
	std::vector<TriangleIndexes> _faceIndices
	{
		TriangleIndexes{0, 1, 2},
		TriangleIndexes{2, 3, 0}
	};
	BlockFaceMeshes _faceMeshes
	{
		std::make_shared<Mesh>(_faceVertices.front, _faceIndices, _blockShader),
		std::make_shared<Mesh>(_faceVertices.back, _faceIndices, _blockShader),
		std::make_shared<Mesh>(_faceVertices.left, _faceIndices, _blockShader),
		std::make_shared<Mesh>(_faceVertices.right, _faceIndices, _blockShader),
		std::make_shared<Mesh>(_faceVertices.top, _faceIndices, _blockShader),
		std::make_shared<Mesh>(_faceVertices.bottom, _faceIndices, _blockShader)
	};
	Shader _blockShader = Shader("src/Data/Shaders/Block.vert", "src/Data/Shaders/Block.frag");
	
	size_t _slotSize;
	std::string _textureAtlasFilename;

public:
	explicit BlockBuilder(std::string textureAtlasFilename, size_t slotSize);

	BlockModel Build(const JsonData& blockData);
};
