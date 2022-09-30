#include "BlockBuilder.h"


void BlockBuilder::DetermineAndSetFaceTexture(const std::string& face, const int x, const int y) const
{
	if (face == "front")	_textureAtlas.SetSprite(_facesTextureCoordinates->front, x, y, false);
	if (face == "back")		_textureAtlas.SetSprite(_facesTextureCoordinates->back, x, y, true);
	if (face == "left")		_textureAtlas.SetSprite(_facesTextureCoordinates->left, x, y, true);
	if (face == "right")	_textureAtlas.SetSprite(_facesTextureCoordinates->right, x, y, false);
	if (face == "top")		_textureAtlas.SetSprite(_facesTextureCoordinates->top, x, y, false);
	if (face == "bottom")	_textureAtlas.SetSprite(_facesTextureCoordinates->bottom, x, y, true);
}

BlockBuilder::BlockBuilder(TextureAtlas& textureAtlas) : _textureAtlas(textureAtlas)
{
}

BlockModel BlockBuilder::Build(const JsonData& blockData) const
{
	for (const auto& textureData : blockData["textures"])
	{
		// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
		const int x = textureData["location"].value("column", 0);
		// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
		const int y = textureData["location"].value("row", 0);

		for (const auto& face : textureData["faces"])
		{
			DetermineAndSetFaceTexture(face, x, y);
		}
	}

	BlockFaces faces
	{
		BlockFaceModel(_facesTextureCoordinates->front),
		BlockFaceModel(_facesTextureCoordinates->back),
		BlockFaceModel(_facesTextureCoordinates->left),
		BlockFaceModel(_facesTextureCoordinates->right),
		BlockFaceModel(_facesTextureCoordinates->top),
		BlockFaceModel(_facesTextureCoordinates->bottom)
	};

	return BlockModel(std::move(faces));
}

