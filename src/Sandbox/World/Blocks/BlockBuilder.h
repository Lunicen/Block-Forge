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
			Vertex{Position{0.0f, 0.0f, 0.0f}, Point{0.0f, 0.0f}},
			Vertex{Position{1.0f, 0.0f, 0.0f}, Point{1.0f, 0.0f}},
			Vertex{Position{1.0f, 1.0f, 0.0f}, Point{1.0f, 1.0f}},
			Vertex{Position{0.0f, 1.0f, 0.0f}, Point{0.0f, 1.0f}},
		};

		std::vector<Vertex> back
		{
			Vertex{Position{0.0f, 0.0f, 1.0f}, Point{0.0f, 0.0f}},
			Vertex{Position{0.0f, 1.0f, 1.0f}, Point{1.0f, 0.0f}},
			Vertex{Position{1.0f, 1.0f, 1.0f}, Point{1.0f, 1.0f}},
			Vertex{Position{1.0f, 0.0f, 1.0f}, Point{0.0f, 1.0f}},
		};
		
		std::vector<Vertex> left
		{
			Vertex{Position{0.0f, 0.0f, 0.0f}, Point{0.0f, 0.0f}},
			Vertex{Position{0.0f, 1.0f, 0.0f}, Point{1.0f, 0.0f}},
			Vertex{Position{0.0f, 1.0f, 1.0f}, Point{1.0f, 1.0f}},
			Vertex{Position{0.0f, 0.0f, 1.0f}, Point{0.0f, 1.0f}},
		};

		std::vector<Vertex> right
		{
			Vertex{Position{1.0f, 0.0f, 0.0f}, Point{0.0f, 0.0f}},
			Vertex{Position{1.0f, 0.0f, 1.0f}, Point{1.0f, 0.0f}},
			Vertex{Position{1.0f, 1.0f, 1.0f}, Point{1.0f, 1.0f}},
			Vertex{Position{1.0f, 1.0f, 0.0f}, Point{0.0f, 1.0f}},
		};
		
		std::vector<Vertex> top
		{
			Vertex{Position{0.0f, 1.0f, 0.0f}, Point{0.0f, 0.0f}},
			Vertex{Position{1.0f, 1.0f, 0.0f}, Point{1.0f, 0.0f}},
			Vertex{Position{1.0f, 1.0f, 1.0f}, Point{1.0f, 1.0f}},
			Vertex{Position{0.0f, 1.0f, 1.0f}, Point{0.0f, 1.0f}},
		};
		
		std::vector<Vertex> bottom
		{
			Vertex{Position{0.0f, 0.0f, 0.0f}, Point{0.0f, 0.0f}},
			Vertex{Position{0.0f, 0.0f, 1.0f}, Point{1.0f, 0.0f}},
			Vertex{Position{1.0f, 0.0f, 1.0f}, Point{1.0f, 1.0f}},
			Vertex{Position{1.0f, 0.0f, 0.0f}, Point{0.0f, 1.0f}},
		};
	} _faceVertices;
	std::vector<TriangleIndexes> _faceIndices
	{
		TriangleIndexes{0, 1, 2},
		TriangleIndexes{2, 3, 0}
	};

	Shader _blockShader = Shader("src/Data/Shaders/Block.vert", "src/Data/Shaders/Block.frag");
	
	size_t _slotSize;
	std::string _textureAtlasFilename;
	
	void SetFaceTexture(const std::string& face, const std::shared_ptr<Texture>& texture);

public:
	explicit BlockBuilder(std::string textureAtlasFilename, size_t slotSize);

	BlockModel Build(const JsonData& blockData);
};
