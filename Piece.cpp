#include "Piece.h"

void Piece::render()
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(red, green, blue);
	glutSolidSphere(size, 64, 64);
	glPopMatrix();
}

