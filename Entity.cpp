#include "Entity.h"

Entity::Entity()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;

	this->red = 0.0f;
	this->green = 0.0f;
	this->blue = 0.0f;

	this->size = 0.0;

	this->selected = false;
}

Entity::Entity(float x, float y, float z, float red, float green, float blue, double size)
{
	this->x = x;
	this->y = y;
	this->z = z;

	this->red = red;
	this->green = green;
	this->blue = blue;

	this->size = size;

	this->selected = false;
} 

Pos Entity::getPos()
{
	Pos pos = { this->x, this->y, this->z };
	return pos;
}

void Entity::setPos(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Entity::setPos(Pos pos)
{
	this->x = pos.x;
	this->y = pos.y;
	this->z = pos.z;
}

void Entity::setColor(float red, float green, float blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}

void Entity::setSize(double size)
{
	this->size = size;
}

void Entity::toggleSelected()
{
	this->selected = !this->selected;
}