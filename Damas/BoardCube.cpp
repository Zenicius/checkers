#include "BoardCube.h"

void BoardCube::render()
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(red, green, blue);
	glutSolidCube(size);
	glPopMatrix();
}