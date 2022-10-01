#version 330 core

layout (location = 0) in vec3 model;
layout (location = 1) in vec2 uv;

uniform mat4 camera;
uniform mat4 position;

out vec2 textureCoordinate; //texture

void main()
{
   gl_Position = camera * position * vec4(model, 1.0);

   textureCoordinate = uv; //texture
}