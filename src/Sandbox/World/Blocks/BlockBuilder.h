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

	struct FaceMeshes
	{
		std::shared_ptr<Mesh> front;
		std::shared_ptr<Mesh> back;
		std::shared_ptr<Mesh> left;
		std::shared_ptr<Mesh> right;
		std::shared_ptr<Mesh> top;
		std::shared_ptr<Mesh> bottom;
	};
	struct FaceTextures
	{
		std::shared_ptr<Texture> front;
		std::shared_ptr<Texture> back;
		std::shared_ptr<Texture> left;
		std::shared_ptr<Texture> right;
		std::shared_ptr<Texture> top;
		std::shared_ptr<Texture> bottom;
	};

	Shader _blockShader = Shader("src/Data/Shaders/Block.vert", "src/Data/Shaders/Block.frag");
	
	size_t _slotSize;
	std::string _textureAtlasFilename;

	static void SetFaceTexture(std::vector<Vertex>& face, const std::shared_ptr<Texture>& texture, std::shared_ptr<Texture>& blockFaceTexture);
	void DetermineAndSetFaceTexture(const std::string& face, const std::shared_ptr<Texture>& texture, FaceTextures& blockFaceTextures);
	BlockModel CreateBlockModel(const FaceTextures& faceTextures);

public:
	explicit BlockBuilder(std::string textureAtlasFilename, size_t slotSize);

	
	BlockModel Build(const JsonData& blockData);
};
