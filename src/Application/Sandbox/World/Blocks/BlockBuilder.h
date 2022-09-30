#pragma once
#include "Core/Metadata.h"
#include "Application/Sandbox/Model/BlockModel.h"
#include "Application/Sandbox/Model/Surface/TextureAtlas.h"

/// @class BlockBuilder
/// @brief A factory that builds and outputs blocks based on their metadata.
class BlockBuilder
{
	struct FacesUvTextureCoordinates
	{
		std::array<Point, 4> front
		{
			Point{0.0f, 0.0f},
			Point{1.0f, 0.0f},
			Point{1.0f, 1.0f},
			Point{0.0f, 1.0f},
		};
		
		std::array<Point, 4> back
		{
			Point{0.0f, 0.0f},
			Point{1.0f, 0.0f},
			Point{1.0f, 1.0f},
			Point{0.0f, 1.0f},
		};
		
		std::array<Point, 4> left
		{
			Point{0.0f, 0.0f},
			Point{1.0f, 0.0f},
			Point{1.0f, 1.0f},
			Point{0.0f, 1.0f},
		};

		std::array<Point, 4> right
		{
			Point{0.0f, 0.0f},
			Point{1.0f, 0.0f},
			Point{1.0f, 1.0f},
			Point{0.0f, 1.0f},
		};
		
		std::array<Point, 4> top
		{
			Point{0.0f, 0.0f},
			Point{1.0f, 0.0f},
			Point{1.0f, 1.0f},
			Point{0.0f, 1.0f},
		};
		
		std::array<Point, 4> bottom
		{
			Point{0.0f, 0.0f},
			Point{1.0f, 0.0f},
			Point{1.0f, 1.0f},
			Point{0.0f, 1.0f},
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

	std::shared_ptr<FacesUvTextureCoordinates> _facesTextureCoordinates = std::make_shared<FacesUvTextureCoordinates>();
	
	void DetermineAndSetFaceTexture(const std::string& face, int x, int y, TextureAtlas& textureAtlas) const;

public:

	/// @brief Builds block based on the data.
	///	@param blockData - Metadata of the block to be built.
	///	@param textureAtlas - Texture atlas related to the block data.
	BlockModel Build(const JsonData& blockData, TextureAtlas& textureAtlas) const;
};
