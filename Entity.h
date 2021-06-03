#pragma once
#include <stdio.h>
#include <GL/glut.h>

struct Pos
{
	float x, y, z;
};

struct Color
{
	float r, g, b;
};

class Entity
{
	protected:
		float x, y, z;
		float red, green, blue;
		double size;
		bool jump;
	public:
		Entity();
		Entity(float x, float y, float z, float red, float green, float blue, double size);

		Pos getPos();
		Color getColor();
		void setPos(float x, float y, float z);
		void setPos(Pos pos);
		void setColor(float red, float green, float blue);
		void setSize(double size);
};

