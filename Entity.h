#pragma once
#include <GL/glut.h>

struct pos
{
	float x, y, z;
};

class Entity
{
	protected:
		float x, y, z;
		float red, green, blue;
		double size;
		bool selected;

	public:
		Entity();
		Entity(float x, float y, float z, float red, float green, float blue, double size);

		pos getPos();
		void setPos(float x, float y, float z);
		void setColor(float red, float green, float blue);
		void setSize(double size);
		void toggleSelected();
};

