#pragma once
#include <GL/glut.h>

class Entity
{
	protected:
		float x, y, z;
		float red, green, blue;
		double size;
	public:
		Entity();
		Entity(float x, float y, float z, float red, float green, float blue, double size);

		void setPos(float x, float y, float z);
		void setColor(float red, float green, float blue);
		void setSize(double size);
};

