#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <GL/glut.h>

class Level
{
	public:
		Level() {};
		void renderTable(float x, float y, float z);
		void renderLeg(float x, float y, float z);
		void render();
};

