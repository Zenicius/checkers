#pragma once
#include <stdio.h>
#include <GL/glut.h>

struct Pos
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

		Pos getPos();
		void setPos(float x, float y, float z);
		void setPos(Pos pos);
		void setColor(float red, float green, float blue);
		void setSize(double size);
		void toggleSelected();
};

