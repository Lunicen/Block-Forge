#pragma once
#include "Core/Metadata.h"
#include "Application/Sandbox/Model/BlockModel.h"
#include "Application/Sandbox/Model/Mesh/Geometry/Shader.h"
#include "Application/Sandbox/Model/Surface/TextureAtlas.h"

/// @class BlockBuilder
/// @brief A factory that builds and outputs blocks based on their metadata.
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

	std::shared_ptr<FaceVertices> _faceVertices = std::make_shared<FaceVertices>();
	std::vector<TriangleIndexes>& _faceIndices;
	std::shared_ptr<TextureAtlas> _textureAtlas;
	Shader& _blockShader;

	void SetFaceTexture(std::vector<Vertex>& face, int x, int y, bool flipTexture) const;
	void DetermineAndSetFaceTexture(const std::string& face, int x, int y);

public:

	/// The constructor.
	///	@param textureAtlasFilename - Path of the file containing the texture atlas of blocks.
	///	@param spriteSize - The size of the sprite.
	///	@param blockIndices - Indices of a block (for optimization purposes).
	/// @param blockShader - Shader of a block (for optimization purposes).
	explicit BlockBuilder(const std::string& textureAtlasFilename, size_t spriteSize, std::vector<TriangleIndexes>& blockIndices, Shader& blockShader);

	/// @brief Builds block based on the data.
	///	@param blockData - metadata of the block to be built.
	BlockModel Build(const JsonData& blockData);
};
