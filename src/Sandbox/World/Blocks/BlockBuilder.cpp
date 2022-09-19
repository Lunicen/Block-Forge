#include "BlockBuilder.h"


void BlockBuilder::SetFaceTexture(
	std::vector<Vertex>& face, 
	const std::shared_ptr<Texture>& texture,
	std::shared_ptr<Texture>& blockFaceTexture)
{
	texture->SetUvVertices(face);
	blockFaceTexture = texture;
}

void BlockBuilder::DetermineAndSetFaceTexture(const std::string& face, const std::shared_ptr<Texture>& texture, FaceTextures& blockFaceTextures)
{
	if (face == "front")	SetFaceTexture(_faceVertices.front, texture, blockFaceTextures.front);
	if (face == "back")		SetFaceTexture(_faceVertices.back, texture, blockFaceTextures.back);
	if (face == "left")		SetFaceTexture(_faceVertices.left, texture, blockFaceTextures.left);
	if (face == "right")	SetFaceTexture(_faceVertices.right, texture, blockFaceTextures.right);
	if (face == "top")		SetFaceTexture(_faceVertices.top, texture, blockFaceTextures.top);
	if (face == "bottom")	SetFaceTexture(_faceVertices.bottom, texture, blockFaceTextures.bottom);
}

BlockModel BlockBuilder::CreateBlockModel(const FaceTextures& faceTextures)
{
	const FaceMeshes faceMeshes
	{
		std::make_shared<Mesh>(_faceVertices.front, _faceIndices, _blockShader),
		std::make_shared<Mesh>(_faceVertices.back, _faceIndices, _blockShader),
		std::make_shared<Mesh>(_faceVertices.left, _faceIndices, _blockShader),
		std::make_shared<Mesh>(_faceVertices.right, _faceIndices, _blockShader),
		std::make_shared<Mesh>(_faceVertices.top, _faceIndices, _blockShader),
		std::make_shared<Mesh>(_faceVertices.bottom, _faceIndices, _blockShader)
	};

	const BlockFaces faces
	{
		std::make_shared<BlockFaceModel>(faceMeshes.front, faceTextures.front),
		std::make_shared<BlockFaceModel>(faceMeshes.back, faceTextures.back),
		std::make_shared<BlockFaceModel>(faceMeshes.left, faceTextures.left),
		std::make_shared<BlockFaceModel>(faceMeshes.right, faceTextures.right),
		std::make_shared<BlockFaceModel>(faceMeshes.top, faceTextures.top),
		std::make_shared<BlockFaceModel>(faceMeshes.bottom, faceTextures.bottom)
	};

	return BlockModel(faces);
}

BlockBuilder::BlockBuilder(std::string textureAtlasFilename, const size_t slotSize)
	: _slotSize(slotSize), _textureAtlasFilename(std::move(textureAtlasFilename))
{
}

BlockModel BlockBuilder::Build(const JsonData& blockData)
{
	FaceTextures faceTextures;

	for (const auto& textureData : blockData["textures"])
	{
		const int x = textureData["location"].value("column", 0);
		const int y = textureData["location"].value("row", 0);

		auto texture = std::make_shared<Texture>(_textureAtlasFilename, x, y, _slotSize);

		for (const auto& face : textureData["faces"])
		{
			DetermineAndSetFaceTexture(face, texture, faceTextures);
		}
	}

	return CreateBlockModel(faceTextures);
}

