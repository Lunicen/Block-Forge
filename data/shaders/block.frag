#version 330 core

out vec4 FragColor;

//texture
in vec2 textureCoordinate;
uniform sampler2D textureSample;
//endofTexture

void main()
{
	//FragColor = vec4(0.8, 0.3, 0.02, 1.0);
	FragColor = texture(textureSample, textureCoordinate); //texture
}