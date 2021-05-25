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
} 

void Entity::setPos(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
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

