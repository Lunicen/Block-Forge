#include "BlockBuilder.h"

void BlockBuilder::SetFaceTexture(
	std::vector<Vertex>& face, 
	const int x, 
	const int y,
	const bool flipTexture) const
{
	_textureAtlas->SetSprite(face, x, y, flipTexture);
}

void BlockBuilder::DetermineAndSetFaceTexture(const std::string& face, const int x, const int y)
{
	if (face == "front")	SetFaceTexture(_faceVertices->front, x, y, false);
	if (face == "back")		SetFaceTexture(_faceVertices->back, x, y, true);
	if (face == "left")		SetFaceTexture(_faceVertices->left, x, y, true);
	if (face == "right")	SetFaceTexture(_faceVertices->right, x, y, false);
	if (face == "top")		SetFaceTexture(_faceVertices->top, x, y, false);
	if (face == "bottom")	SetFaceTexture(_faceVertices->bottom, x, y, true);
}

BlockBuilder::BlockBuilder(const std::string& textureAtlasFilename, const size_t spriteSize, std::vector<TriangleIndexes>& blockIndices, Shader& blockShader)
	: _faceIndices(blockIndices),
	  _textureAtlas(std::make_shared<TextureAtlas>(textureAtlasFilename, spriteSize)),
	  _blockShader(blockShader)
{
}

BlockModel BlockBuilder::Build(const JsonData& blockData)
{
	for (const auto& textureData : blockData["textures"])
	{
		const int x = textureData["location"].value("column", 0);
		const int y = textureData["location"].value("row", 0);

		for (const auto& face : textureData["faces"])
		{
			DetermineAndSetFaceTexture(face, x, y);
		}
	}

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
		BlockFaceModel(faceMeshes.front, _textureAtlas),
		BlockFaceModel(faceMeshes.back, _textureAtlas),
		BlockFaceModel(faceMeshes.left, _textureAtlas),
		BlockFaceModel(faceMeshes.right, _textureAtlas),
		BlockFaceModel(faceMeshes.top, _textureAtlas),
		BlockFaceModel(faceMeshes.bottom, _textureAtlas)
	};

	return BlockModel(std::move(faces));
}

