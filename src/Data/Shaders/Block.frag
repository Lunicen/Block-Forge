#version 330 core

out vec4 FragColor;

//texture
in vec2 texCoord;
uniform sampler2D tex0;
//endofTexture

void main()
{
	//FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);
	FragColor = texture(tex0, texCoord); //texture
}