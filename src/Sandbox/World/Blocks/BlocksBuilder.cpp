#include "BlocksBuilder.h"

void BlocksBuilder::SetFaceTexture(
	std::vector<Vertex>& face, 
	const std::shared_ptr<Texture>& texture,
	std::shared_ptr<Texture>& blockFaceTexture)
{
	texture->SetUvToTextureAtlas(face);
	blockFaceTexture = texture;
}

void BlocksBuilder::DetermineAndSetFaceTexture(const std::string& face, const std::shared_ptr<Texture>& texture, FaceTextures& blockFaceTextures) const
{
	if (face == "front")	SetFaceTexture(_faceVertices->front, texture, blockFaceTextures.front);
	if (face == "back")		SetFaceTexture(_faceVertices->back, texture, blockFaceTextures.back);
	if (face == "left")		SetFaceTexture(_faceVertices->left, texture, blockFaceTextures.left);
	if (face == "right")	SetFaceTexture(_faceVertices->right, texture, blockFaceTextures.right);
	if (face == "top")		SetFaceTexture(_faceVertices->top, texture, blockFaceTextures.top);
	if (face == "bottom")	SetFaceTexture(_faceVertices->bottom, texture, blockFaceTextures.bottom);
}

BlockModel BlocksBuilder::CreateBlockModel(const FaceTextures& faceTextures) const
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

BlocksBuilder::BlocksBuilder(std::string textureAtlasFilename, const size_t slotSize, std::vector<TriangleIndexes>& blockIndices, Shader& blockShader)
	: _faceVertices(std::make_shared<FaceVertices>()), _faceIndices(blockIndices), _slotSize(slotSize),
	  _textureAtlasFilename(std::move(textureAtlasFilename)), _blockShader(blockShader)
{
}

BlockModel BlocksBuilder::Build(const JsonData& blockData)
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

