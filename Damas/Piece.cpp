#include "Piece.h"

void Piece::setJumpPiece(bool option)
{
	this->jump = option;
}

bool Piece::isJumpPiece()
{
	return this->jump;
}

void Piece::setKing(bool option)
{
	this->king = option;
}

bool Piece::isKing()
{
	return this->king;
}

void Piece::startAnimation(float x, float y, float z, float tStart, float duration)
{
	this->animation.setDest(x, y, z, tStart, duration);
	this->animation.start();
}

void Piece::tick(float t) 
{
	if (this->animation.isRunning())
	{
		if (t - animation.getStartTime() >= animation.getDuration())
		{
			animation.stop();
			this->setPos(animation.getDest().x, this->getPos().y, animation.getDest().z);
		}
		else
		{
			float finalT = (t - animation.getStartTime()) / animation.getDuration();
			float finalX = (animation.getDest().x - this->getPos().x) * finalT + this->getPos().x;
			float finalZ = (animation.getDest().z - this->getPos().z) * finalT + this->getPos().z;

			this->setPos(finalX, this->getPos().y, finalZ);
		}
	}
}

Pos Piece::getFinalPos()
{
	Pos pos;
	if (this->animation.isRunning())
	{
		pos = { this->animation.getDest().x, this->animation.getDest().y, this->animation.getDest().z };
	}
	else pos = { this->x, this->y, this->z };

	return pos;
}

void Piece::render()
{	
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotated(90, -1, 0, 0);
	glColor3f(red, green, blue);
	gluDisk(this->QUAD, 0, size, 64, 64);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, y, z);
	glRotated(90, -1, 0, 0);
	glColor3f(red, green, blue);
	gluCylinder(this->QUAD, size, size, size / 2, 64, 64);
	glPopMatrix();
}