#include "Piece.h"

void Piece::setJumpPiece(bool option)
{
	this->jump = option;
}

bool Piece::isJumpPiece()
{
	return this->jump;
}

void Piece::render()
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(red, green, blue);
	glutSolidSphere(size, 64, 64);
	glPopMatrix();
}