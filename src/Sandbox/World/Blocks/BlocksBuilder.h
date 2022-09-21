#pragma once
#include "Core/Metadata.h"
#include "Sandbox/Model/BlockModel.h"
#include "Sandbox/Model/Mesh/Geometry/Shader.h"

class BlocksBuilder
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
			Vertex{Position{1.0f, 0.0f, 1.0f}, Point{1.0f, 0.0f}},
			Vertex{Position{1.0f, 1.0f, 1.0f}, Point{1.0f, 1.0f}},
			Vertex{Position{0.0f, 1.0f, 1.0f}, Point{0.0f, 1.0f}},
		};
		
		std::vector<Vertex> left
		{
			Vertex{Position{0.0f, 0.0f, 0.0f}, Point{0.0f, 0.0f}},
			Vertex{Position{0.0f, 0.0f, 1.0f}, Point{1.0f, 0.0f}},
			Vertex{Position{0.0f, 1.0f, 1.0f}, Point{1.0f, 1.0f}},
			Vertex{Position{0.0f, 1.0f, 0.0f}, Point{0.0f, 1.0f}},
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
	};

	struct FaceMeshes
	{
		std::unique_ptr<Mesh> front;
		std::unique_ptr<Mesh> back;
		std::unique_ptr<Mesh> left;
		std::unique_ptr<Mesh> right;
		std::unique_ptr<Mesh> top;
		std::unique_ptr<Mesh> bottom;
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

	std::shared_ptr<FaceVertices> _faceVertices;
	std::vector<TriangleIndexes>& _faceIndices;

	size_t _slotSize;
	std::string _textureAtlasFilename;
	Shader& _blockShader;

	static void SetFaceTexture(std::vector<Vertex>& face, const std::shared_ptr<Texture>& texture, std::shared_ptr<Texture>& blockFaceTexture);
	void DetermineAndSetFaceTexture(const std::string& face, const std::shared_ptr<Texture>& texture, FaceTextures& blockFaceTextures) const;
	BlockModel CreateBlockModel(const FaceTextures& faceTextures) const;

public:
	explicit BlocksBuilder(std::string textureAtlasFilename, size_t slotSize, std::vector<TriangleIndexes>& blockIndices, Shader& blockShader);

	BlockModel Build(const JsonData& blockData);
};
