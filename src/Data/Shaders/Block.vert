#version 330 core

layout (location = 0) in vec3 model;

uniform mat4 camera;
uniform mat4 position;

void main()
{
   gl_Position = camera * position * vec4(model, 1.0);
}