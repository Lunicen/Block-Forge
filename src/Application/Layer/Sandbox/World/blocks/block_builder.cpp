#include "application/layer/sandbox/world/blocks/block_builder.h"


void BlockBuilder::DetermineAndSetFaceTexture(const std::string_view face, const int x, const int y, TextureAtlas& textureAtlas) const
{
	if (face == "front")	textureAtlas.SetSprite(_facesTextureCoordinates->front, x, y, false);
	if (face == "back")		textureAtlas.SetSprite(_facesTextureCoordinates->back, x, y, true);
	if (face == "left")		textureAtlas.SetSprite(_facesTextureCoordinates->left, x, y, true);
	if (face == "right")	textureAtlas.SetSprite(_facesTextureCoordinates->right, x, y, false);
	if (face == "top")		textureAtlas.SetSprite(_facesTextureCoordinates->top, x, y, true);
	if (face == "bottom")	textureAtlas.SetSprite(_facesTextureCoordinates->bottom, x, y, true);
}

BlockModel BlockBuilder::Build(const JsonData& blockData, TextureAtlas& textureAtlas) const
{
	for (const auto& textureData : blockData["textures"])
	{
		// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
		const int x = textureData["location"].value("column", 0);
		// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
		const int y = textureData["location"].value("row", 0);

		for (const auto& face : textureData["faces"])
		{
			DetermineAndSetFaceTexture(face, x, y, textureAtlas);
		}
	}

	const BlockFaces faces
	{
		BlockFaceModel(_facesTextureCoordinates->front),
		BlockFaceModel(_facesTextureCoordinates->back),
		BlockFaceModel(_facesTextureCoordinates->left),
		BlockFaceModel(_facesTextureCoordinates->right),
		BlockFaceModel(_facesTextureCoordinates->top),
		BlockFaceModel(_facesTextureCoordinates->bottom)
	};

	return BlockModel(faces);
}

