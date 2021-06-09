#include "Piece.h"

void Piece::setJumpPiece(bool option)
{
	this->jump = option;
}

void Piece::startAnimation(float x, float y, float z, float tStart, float duration)
{
	this->animation.setDest(x, y, z, tStart, duration);
	this->animation.start();
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

bool Piece::isJumpPiece()
{
	return this->jump;
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

void Piece::render()
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(red, green, blue);
	glutSolidSphere(size, 64, 64);
	glPopMatrix();
}