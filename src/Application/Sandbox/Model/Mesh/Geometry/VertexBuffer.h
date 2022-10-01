#pragma once
#include <vector>
#include "Structures.h"
#include <glad/glad.h>

/// @class VertexBuffer
/// @brief A Vertex Buffer Object handler - wrapper for the VBO functionality.
class VertexBuffer
{
	GLuint _bufferRef = 0;

public:



	explicit VertexBuffer(const std::vector<Point3D>& vertices);

	/// @brief The constructor creates VBO, binds it immediately and sets its data.
	///	@warning This constructor creates **STATIC** vertex buffer object.
	///	It's meant to represent single objects or to be used with instancing.
	explicit VertexBuffer(const std::vector<Vertex>& vertices);

	/// @brief The constructor creates VBO, binds it immediately and sets its data.
	///	@warning This constructor **allocates** **DYNAMIC** vertex buffer object.
	///	It's meant to be flexible and it's empty!
	explicit VertexBuffer(const size_t& vertexSize, const size_t& maxAmountOfVertices);

	VertexBuffer(const VertexBuffer&) = delete;

	/// @brief Move constructor.
	VertexBuffer(VertexBuffer&&) = default;

	VertexBuffer& operator=(const VertexBuffer&) = delete;

	/// @brief Move assignment constructor.
	VertexBuffer& operator=(VertexBuffer&&) = default;

	/// @brief Tells OpenGL to bind the VBO.
	void Bind() const;

	/// @brief Tells OpenGL to unbind the VBO.
	void Unbind() const;

	~VertexBuffer();
};

