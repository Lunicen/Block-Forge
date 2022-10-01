#include "Hud.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>

#include "Model/Surface/Texture.h"


//Vertices//////////////////////////////////////////////
GLfloat vertices[] = 
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, //Upper corner

	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f //inner down
};

GLuint indices[] =
{
	0, 3, 5, //lower left triangle
	3, 2, 4, //lower right triangle
	5, 4, 1 // Upper triangle
};
///////////////////////////////////////////////////////

Hud::Hud()
{
	//_texture.Bind(_shader);
	//Shader shaderProgram("default.vert", "default.frag");



}

void Hud::Draw()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, 800, 640, 0.0, -1.0, 10.0); //zrobic zeby wielkosc byla dopasowana do settingow //sprawdzic glOrtho2d
	glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();

	glLoadIdentity();
	glDisable(GL_CULL_FACE); //eh problem na problemie

	glClear(GL_DEPTH_BUFFER_BIT);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(10.0, 0.0);
	glVertex2f(10.0, 10.0);
	glVertex2f(0.0, 10.0);
	glEnd();


	//making sure we can render 3d again
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	//glPopMatrix();
	
}

void Hud::Draw2()
{
	_mesh.Draw();
}