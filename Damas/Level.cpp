#include "Level.h"

Level::Level()
{
}

void Level::renderFloor()
{
	glPushMatrix();
	glTranslatef(-100, -33, -100);
	glBegin(GL_QUADS);
		glColor3f(1.28, 1.28f, 1.28f);     // WHITE
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 300.0f);
		glVertex3f(300.0f, 0.0f, 300.0f);
		glVertex3f(300.0f, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();
}

void Level::renderTable(float x, float y, float z)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glBegin(GL_QUADS);

		glColor3f(0.0f, 1.0f, 0.0f);     // Green
		glVertex3f(20.0f, 1.0f, -30.0f);
		glVertex3f(-20.0f, 1.0f, -30.0f);
		glVertex3f(-20.0f, 1.0f, 20.0f);
		glVertex3f(20.0f, 1.0f, 20.0f);

		glColor3f(1.0f, 0.5f, 0.0f);     // Orange
		glVertex3f(20.0f, -1.0f, 20.0f);
		glVertex3f(-20.0f, -1.0f, 20.0f);
		glVertex3f(-20.0f, -1.0f, -30.0f);
		glVertex3f(20.0f, -1.0f, -30.0f);

		glColor3f(1.0f, 0.0f, 0.0f);     // Red
		glVertex3f(20.0f, 1.0f, 20.0f);
		glVertex3f(-20.0f, 1.0f, 20.0f);
		glVertex3f(-20.0f, -1.0f, 20.0f);
		glVertex3f(20.0f, -1.0f, 20.0f);

		glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
		glVertex3f(20.0f, -1.0f, -30.0f);
		glVertex3f(-20.0f, -1.0f, -30.0f);
		glVertex3f(-20.0f, 1.0f, -30.0f);
		glVertex3f(20.0f, 1.0f, -30.0f);

		glColor3f(0.0f, 0.0f, 1.0f);     // Blue
		glVertex3f(-20.0f, 1.0f, 20.0f);
		glVertex3f(-20.0f, 1.0f, -30.0f);
		glVertex3f(-20.0f, -1.0f, -30.0f);
		glVertex3f(-20.0f, -1.0f, 20.0f);

		glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
		glVertex3f(20.0f, 1.0f, -30.0f);
		glVertex3f(20.0f, 1.0f, 20.0f);
		glVertex3f(20.0f, -1.0f, 20.0f);
		glVertex3f(20.0f, -1.0f, -30.0f);

	glEnd();  
	glPopMatrix();
}

void Level::renderLeg(float x, float y, float z)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glBegin(GL_QUADS);

		glColor3f(0.0f, 1.0f, 0.0f);     // Green
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		glColor3f(1.0f, 0.5f, 0.0f);     // Orange
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glColor3f(1.0f, 0.0f, 0.0f);     // Red
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -30.0f, 1.0f);
		glVertex3f(1.0f, -30.0f, 1.0f);

		glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
		glVertex3f(1.0f, -30.0f, -1.0f);
		glVertex3f(-1.0f, -30.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);

		glColor3f(0.0f, 0.0f, 1.0f);     // Blue
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, -30.0f, -1.0f);
		glVertex3f(-1.0f, -30.0f, 1.0f);

		glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -30.0f, 1.0f);
		glVertex3f(1.0f, -30.0f, -1.0f);

	glEnd();
	glPopMatrix();
}



void Level::render()
{
	// FLOOR
	renderFloor();

	// TABLE TOP
	renderTable(3.5f, -2.0f, 3.0f);

	// TABLE BOTTOM RIGHT
	renderLeg(20.5f, -3.0f, 20.0f);

	// TABLE BOTTOM LEFT
	renderLeg(-13.0f, -3.0f, 20.0f);

	// TABLE TOP RIGHT
	renderLeg(20.5f, -3.0f, -23.0f);

	// TABLE TOP LEFT
	renderLeg(-13.0f, -3.0f, -23.0f);
}
