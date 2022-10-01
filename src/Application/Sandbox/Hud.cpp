#include "Hud.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>

#include "Model/Surface/Texture.h"

Hud::Hud()
{
	_texture.Bind(_shader); //zapytaæ czy tutaj dac po prostu tak //GL_TEXTURE0 ???
	/*
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex2f(0.05, 0.05);
	glTexCoord2f(1.0, 1.0); glVertex2f(0.3, 0.05);
	glTexCoord2f(1.0, 0.0); glVertex2f(0.3, 0.15);
	glTexCoord2f(0.0, 0.0); glVertex2f(0.05, 0.15);
	glEnd();
	*/
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
