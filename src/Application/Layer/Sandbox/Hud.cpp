#include "Hud.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>

#include "Model/Surface/Texture.h"

Hud::Hud()
{
	//_texture.Bind(_shader);
	//Shader shaderProgram("default.vert", "default.frag");
}


void Hud::Draw()
{
	_mesh.Draw(_texture);
}