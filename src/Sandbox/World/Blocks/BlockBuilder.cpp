#include "BlockBuilder.h"

void BlockBuilder::SetFaceTexture(
	std::vector<Vertex>& face, 
	const std::shared_ptr<Texture>& texture,
	std::shared_ptr<Texture>& blockFaceTexture,
	const bool flipTexture)
{
	texture->SetUvToTextureAtlas(face, flipTexture);
	blockFaceTexture = texture;
}

void BlockBuilder::DetermineAndSetFaceTexture(const std::string& face, const std::shared_ptr<Texture>& texture, FaceTextures& blockFaceTextures) const
{
	if (face == "front")	SetFaceTexture(_faceVertices->front, texture, blockFaceTextures.front, false);
	if (face == "back")		SetFaceTexture(_faceVertices->back, texture, blockFaceTextures.back, true);
	if (face == "left")		SetFaceTexture(_faceVertices->left, texture, blockFaceTextures.left, true);
	if (face == "right")	SetFaceTexture(_faceVertices->right, texture, blockFaceTextures.right, false);
	if (face == "top")		SetFaceTexture(_faceVertices->top, texture, blockFaceTextures.top, false);
	if (face == "bottom")	SetFaceTexture(_faceVertices->bottom, texture, blockFaceTextures.bottom, true);
}

BlockModel BlockBuilder::CreateBlockModel(const FaceTextures& faceTextures) const
{
	FaceMeshes faceMeshes
	{
		std::make_unique<Mesh>(_faceVertices->front, _faceIndices, _blockShader),
		std::make_unique<Mesh>(_faceVertices->back, _faceIndices, _blockShader),
		std::make_unique<Mesh>(_faceVertices->left, _faceIndices, _blockShader),
		std::make_unique<Mesh>(_faceVertices->right, _faceIndices, _blockShader),
		std::make_unique<Mesh>(_faceVertices->top, _faceIndices, _blockShader),
		std::make_unique<Mesh>(_faceVertices->bottom, _faceIndices, _blockShader)
	};

	BlockFaces faces
	{
		BlockFaceModel(faceMeshes.front, faceTextures.front),
		BlockFaceModel(faceMeshes.back, faceTextures.back),
		BlockFaceModel(faceMeshes.left, faceTextures.left),
		BlockFaceModel(faceMeshes.right, faceTextures.right),
		BlockFaceModel(faceMeshes.top, faceTextures.top),
		BlockFaceModel(faceMeshes.bottom, faceTextures.bottom)
	};

	return BlockModel(std::move(faces));
}

BlockBuilder::BlockBuilder(std::string textureAtlasFilename, const size_t spriteSize, std::vector<TriangleIndexes>& blockIndices, Shader& blockShader)
	: _faceIndices(blockIndices), _slotSize(spriteSize),
	  _textureAtlasFilename(std::move(textureAtlasFilename)), _blockShader(blockShader)
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

