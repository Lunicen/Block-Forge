#version 330 core

layout (location = 0) in vec3 model;

void main()
{
   gl_Position = vec4(model, 1.0);
}