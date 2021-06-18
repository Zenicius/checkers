#pragma once
#include <stdio.h>
#include <GL/glut.h>

class Level
{
	public:
		Level();
		void renderFloor();
		void renderTable(float x, float y, float z);
		void renderLeg(float x, float y, float z);
		void render();
};

