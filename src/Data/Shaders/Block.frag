#version 330 core

out vec4 FragColor;

//texture
in vec2 textureCoordinate;
uniform sampler2D textureSample;
//endofTexture

void main()
{
	//FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);
	FragColor = texture(textureSample, textureCoordinate); //texture
}