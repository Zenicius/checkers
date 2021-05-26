#include "Piece.h"

void Piece::movePiece(BoardCube boardCube)
{
	setPos(boardCube.getPos().x, 1.0f, boardCube.getPos().z);
}

void Piece::render()
{
	glPushMatrix();
	glTranslatef(x, y, z);
	if (selected) 
	{
		glColor3f(255.0f, 0.0f, 0.0f);
	}
	else glColor3f(red, green, blue);
	glutSolidSphere(size, 64, 64);
	glPopMatrix();
}

