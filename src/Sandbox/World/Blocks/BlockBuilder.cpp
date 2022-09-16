#include "BlockBuilder.h"

void BlockBuilder::SetFaceTexture(const std::string& face, const std::shared_ptr<Texture>& texture)
{
	if (face == "front")	texture->SetUvVertices(_faceVertices.front);
	if (face == "back")		texture->SetUvVertices(_faceVertices.back);
	if (face == "left")		texture->SetUvVertices(_faceVertices.left);
	if (face == "right")	texture->SetUvVertices(_faceVertices.right);
	if (face == "top")		texture->SetUvVertices(_faceVertices.top);
	if (face == "bottom")	texture->SetUvVertices(_faceVertices.bottom);
}

BlockBuilder::BlockBuilder(std::string textureAtlasFilename, const size_t slotSize)
	: _slotSize(slotSize), _textureAtlasFilename(std::move(textureAtlasFilename))
{
}

BlockModel BlockBuilder::Build(const JsonData& blockData)
{
	for (const auto& textureData : blockData["textures"])
	{
		const size_t x = textureData["location"].value("column", 0);
		const size_t y = textureData["location"].value("row", 0);

		auto texture = std::make_shared<Texture>(_textureAtlasFilename, x, y, _slotSize);

		for (const auto& face : textureData["faces"])
		{
			SetFaceTexture(face, texture);
		}
	}

	const BlockFaceMeshes faceMeshes
	{
		std::make_shared<Mesh>(_faceVertices.front, _faceIndices, _blockShader),
		std::make_shared<Mesh>(_faceVertices.back, _faceIndices, _blockShader),
		std::make_shared<Mesh>(_faceVertices.left, _faceIndices, _blockShader),
		std::make_shared<Mesh>(_faceVertices.right, _faceIndices, _blockShader),
		std::make_shared<Mesh>(_faceVertices.top, _faceIndices, _blockShader),
		std::make_shared<Mesh>(_faceVertices.bottom, _faceIndices, _blockShader)
	};

	return BlockModel(faceMeshes);
}

