#include<windows.h>
#include <GL/glut.h>


const char* title = "Damas";
int width = 1366;
int height = 728;

GLfloat rotateAngle = 0.0;

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200);
	gluLookAt(0.0f, 20.5f, 15.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);
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

void renderBlackArea()
{
	glBegin(GL_QUADS);
	glColor3f(0.05f, 0.05f, 0.05f);
	glTranslatef(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.50f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.3f, 0.0f);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.05f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -1.5f);
	glVertex3f(0.0f, 0.3f, -1.5f);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.05f, 0.05f, 0.05f);
	glVertex3f(1.5f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.0f, -1.5f);
	glVertex3f(1.5f, 0.3f, -1.5f);
	glVertex3f(1.5f, 0.3f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.05f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.0f, -1.5f);
	glVertex3f(1.50f, 0.0f, -1.5f);
	glVertex3f(1.5f, 0.3f, -1.5f);
	glVertex3f(0.0f, 0.3f, -1.5f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.05f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.50f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.0f, -1.5f);
	glVertex3f(0.0f, 0.0f, -1.5f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glVertex3f(1.50f, 0.3f, 0.0f);
	glVertex3f(1.5f, 0.3f, -1.5f);
	glVertex3f(0.0f, 0.3f, -1.5f);
	glEnd();
}

void renderWhiteArea()
{
	// BOTTOM 
	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f); // WHITE
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.50f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.3f, 0.0f);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glEnd();

	// LEFT 
	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -1.5f);
	glVertex3f(0.0f, 0.3f, -1.5f);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glEnd();

	// RIGHT
	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glVertex3f(1.5f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.0f, -1.5f);
	glVertex3f(1.5f, 0.3f, -1.5f);
	glVertex3f(1.5f, 0.3f, 0.0f);
	glEnd();

	// TOP ???
	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glVertex3f(0.0f, 0.0f, -1.5f);
	glVertex3f(1.50f, 0.0f, -1.5f);
	glVertex3f(1.5f, 0.3f, -1.5f);
	glVertex3f(0.0f, 0.3f, -1.5f);
	glEnd();

	// MIDLE ??
	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.50f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.0f, -1.5f);
	glVertex3f(0.0f, 0.0f, -1.5f);
	glEnd();

	// ???
	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glVertex3f(1.50f, 0.3f, 0.0f);
	glVertex3f(1.5f, 0.3f, -1.5f);
	glVertex3f(0.0f, 0.3f, -1.5f);
	glEnd();
}

void renderBoard()
{
	float i;
	int k = 0;
	for (float j = 0.0; j > (-8 * 1.5); j -= 1.5)
	{
		k++;
		for (i = 0.0; i < (4 * 3.0); i += 3.0)
		{
			if (k % 2 == 0)
			{
				glPushMatrix();
				glTranslatef(i, 0.0, j);
				renderBlackArea();
				glPopMatrix();

			}
			else
			{
				glPushMatrix();
				glTranslatef(i + 1.5, 0.0, j);
				renderBlackArea();
				glPopMatrix();
			}
		}
	}
}


void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.0f, 0.6f, 0.0f, 1.0f);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(rotateAngle, 1.0f, 0.0f, 0.0f);
	glTranslatef(-4 * 1.5, 0.0, 4 * 1.5);

	renderBoard(); 

	glutSwapBuffers();
}

void tick(int value) 
{
	rotateAngle += 1.0f;
	if (rotateAngle > 360)
	{
		rotateAngle -= 360;
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