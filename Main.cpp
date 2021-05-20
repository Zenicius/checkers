/*
* DAMAS 
* VINICIUS REIS
*/

#include <stdio.h>
#include <windows.h>
#include <GL/glut.h>

const char* title = "Damas";
int width = 1366;
int height = 728;

bool rotate = false;
GLfloat rotateAngle = 0.0;

void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.0f, 0.6f, 0.0f, 1.0f);
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200);
}

void keyboardInput(unsigned char key, int x, int y)
{
	switch (key) 
	{
		case 27:
			exit(0);
			break;
		case 'f':
			glutFullScreen();
			break;
	}
}

void renderText(float x, float y, void* font, const char* string, float red, float green, float blue) 
{
	glPushMatrix();
	glColor3f(red, green, blue);
	glRasterPos2f(x, y);
	while (*string)
	{	
		glutBitmapCharacter(font, *string++);
	}
	glPopMatrix();
}

void renderBoard()
{
	int k = 0;
	
	// RENDER BLACK AREA
	for (float j = 0.0; j < 8; j++)
	{
		k++;
		for (float i = 0.0; i < 4; i++)
		{
			if (k % 2 == 0)
			{
				glPushMatrix();
				glTranslatef(i * 3, 0.0, j * 1.5);
				glColor3f(0.35f, 0.24f, 0.13f);
				glutSolidCube(1.5f);
				glPopMatrix();

			}
			else
			{
				glPushMatrix();
				glTranslatef((i * 3 + 1.5), 0.0, j * 1.5);
				glColor3f(0.35f, 0.24f, 0.13f);
				glutSolidCube(1.5f);
				glPopMatrix();
			}
		}
	}

	// RENDER WHITE AREA
	for (float j = 0.0; j < 8; j++)
	{
		k++;
		for (float i = 0.0; i < 4; i++)
		{
			if (k % 2 == 0)
			{
				glPushMatrix();
				glTranslatef((i * 3 + 1.5), 0.0, j * 1.5);
				glColor3f(1.05f, 0.90f, 0.70f);
				glutSolidCube(1.5f);
				glPopMatrix();
			}
			else
			{
				glPushMatrix();
				glTranslatef((i * 3), 0.0, j * 1.5);
				glColor3f(1.05f, 0.90f, 0.70f);
				glutSolidCube(1.5f);
				glPopMatrix();
			}
		}
	}
}

void renderPieces()
{
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0f, 10.0f, 30.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	renderText(-22, 10, GLUT_BITMAP_TIMES_ROMAN_24, "TEST", 0, 0, 0);

	glRotatef(rotateAngle, 1.0f, 0.0f, 0.0f);
	glTranslatef(-5.5, 0.0, 4 * 1.5);

	renderBoard(); 
	renderPieces();

	glutSwapBuffers();
}

void tick(int value) 
{
	if (rotate)
	{
		rotateAngle += 1.0f;
		if (rotateAngle > 360)
		{
			rotateAngle -= 360;
		}
	}
	
	glutPostRedisplay();
	glutTimerFunc(25, tick, 0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height); 
	glutCreateWindow(title);
	//glutFullScreen(); 

	init();

	glutDisplayFunc(render); // RENDER
	glutReshapeFunc(resize); // RESIZE

	glutKeyboardFunc(keyboardInput); // KEYS INPUT
	glutTimerFunc(25, tick, 0); // UPDATE

	glutMainLoop();

	return 0;
}