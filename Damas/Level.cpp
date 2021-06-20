#include "Level.h"

void Level::renderTable(float x, float y, float z)
{
	glPushMatrix();

	glTranslatef(x, y, z);
	glBegin(GL_QUADS);

		glColor3f(0.15f, 0.075f, 0.0f);    
		glVertex3f(20.0f, 1.0f, -30.0f);
		glVertex3f(-20.0f, 1.0f, -30.0f);
		glVertex3f(-20.0f, 1.0f, 20.0f);
		glVertex3f(20.0f, 1.0f, 20.0f);

		glColor3f(0.15f, 0.075f, 0.0f);       
		glVertex3f(20.0f, -1.0f, 20.0f);
		glVertex3f(-20.0f, -1.0f, 20.0f);
		glVertex3f(-20.0f, -1.0f, -30.0f);
		glVertex3f(20.0f, -1.0f, -30.0f);

		glColor3f(0.15f, 0.075f, 0.0f);      
		glVertex3f(20.0f, 1.0f, 20.0f);
		glVertex3f(-20.0f, 1.0f, 20.0f);
		glVertex3f(-20.0f, -1.0f, 20.0f);
		glVertex3f(20.0f, -1.0f, 20.0f);

		glColor3f(0.15f, 0.075f, 0.0f);       
		glVertex3f(20.0f, -1.0f, -30.0f);
		glVertex3f(-20.0f, -1.0f, -30.0f);
		glVertex3f(-20.0f, 1.0f, -30.0f);
		glVertex3f(20.0f, 1.0f, -30.0f);

		glColor3f(0.15f, 0.075f, 0.0f);      
		glVertex3f(-20.0f, 1.0f, 20.0f);
		glVertex3f(-20.0f, 1.0f, -30.0f);
		glVertex3f(-20.0f, -1.0f, -30.0f);
		glVertex3f(-20.0f, -1.0f, 20.0f);

		glColor3f(0.15f, 0.075f, 0.0f);      
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

		glColor3f(0.20f, 0.090f, 0.0f);      
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		glColor3f(0.20f, 0.090f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glColor3f(0.20f, 0.090f, 0.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -30.0f, 1.0f);
		glVertex3f(1.0f, -30.0f, 1.0f);

		glColor3f(0.20f, 0.090f, 0.0f);
		glVertex3f(1.0f, -30.0f, -1.0f);
		glVertex3f(-1.0f, -30.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);

		glColor3f(0.20f, 0.090f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, -30.0f, -1.0f);
		glVertex3f(-1.0f, -30.0f, 1.0f);

		glColor3f(0.20f, 0.090f, 0.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -30.0f, 1.0f);
		glVertex3f(1.0f, -30.0f, -1.0f);

	glEnd();
	glPopMatrix();
}

void Level::render()
{
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
