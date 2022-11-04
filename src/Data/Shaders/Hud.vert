#version 330 core

layout (location = 0) in vec3 model;
layout (location = 1) in vec2 uv;

out vec2 textureCoordinate; //texture

void main()
{
   gl_Position = vec4(model, 1.0);

   textureCoordinate = uv; //texture
}