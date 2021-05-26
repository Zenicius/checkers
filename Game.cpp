/*
* DAMAS
* VINICIUS REIS
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#include "Entity.h"
#include "Board.h"
#include "Piece.h"

// GAME STATES
#define MENU_STATE 0
#define PLAYER1_TURN 1
#define PLAYER2_TURN 2
#define PLAYER1_WON 11
#define PLAYER2_WON 12

const char* title = "Damas";
int width = 1366;
int height = 728;

int gameState = MENU_STATE;

Board board;
int pieceIndex = -1;

bool showDebug = true;
bool rotate = false;

int mouseX = 0;
int lastMouseX = 0;
int mouseY = 0;
int lastMouseY = 0;

char lastKeyPressed[30] = "None";

bool cameraMove = false;
float rotateAngle = 0.0f;
float cameraValueX = 117939.0f; // CENTER 
float cameraValueY = 0.0;
float zoomValue = 15.0f;

void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.0f, 0.6f, 0.0f, 1.0f);
}

void cursorIncrease()
{
	if (gameState == PLAYER1_TURN)
	{
		if (pieceIndex >= 0)
		{
			board.piecesWhite[pieceIndex].toggleSelected();
		} 

		if (pieceIndex < 11)
		{
			pieceIndex++;
			board.piecesWhite[pieceIndex].toggleSelected();
		}
		else
		{
			pieceIndex = 0;
			board.piecesWhite[pieceIndex].toggleSelected();
		}
	}
	else if (gameState == PLAYER2_TURN)
	{
		if (pieceIndex >= 0)
		{
			board.piecesBlack[pieceIndex].toggleSelected();
		}

		if (pieceIndex < 11)
		{
			pieceIndex++;
			board.piecesBlack[pieceIndex].toggleSelected();
		}
		else
		{
			pieceIndex = 0;
			board.piecesBlack[pieceIndex].toggleSelected();
		}
	}
}

void cursorDecrease()
{
	if (gameState == PLAYER1_TURN)
	{
		if (pieceIndex >= 0)
		{
			board.piecesWhite[pieceIndex].toggleSelected();
		}

		if (pieceIndex > 0)
		{
			pieceIndex--;
			board.piecesWhite[pieceIndex].toggleSelected();
		}
		else
		{
			pieceIndex = 11;
			board.piecesWhite[pieceIndex].toggleSelected();
		}
	}
	else if (gameState == PLAYER2_TURN)
	{
		if (pieceIndex >= 0)
		{
			board.piecesBlack[pieceIndex].toggleSelected();
		}

		if (pieceIndex > 0)
		{
			pieceIndex--;
			board.piecesBlack[pieceIndex].toggleSelected();
		}
		else
		{
			pieceIndex = 11;
			board.piecesBlack[pieceIndex].toggleSelected();
		}
	}
}

void changePlayerTurn()
{
	// CHANGE TO OTHER PLAYER VIEW
	cameraValueX = 117939.0f;
	if (rotateAngle == 180.0f) rotateAngle = 0.0f;
	else rotateAngle = 180.0f;

	if (gameState == PLAYER2_TURN)
	{
		board.piecesBlack[pieceIndex].toggleSelected();
		gameState = PLAYER1_TURN;
		pieceIndex = 0;
	}
	else 
	{
		board.piecesWhite[pieceIndex].toggleSelected();
		gameState = PLAYER2_TURN;
		pieceIndex = 0;
	}
}

void startGame()
{
	gameState = PLAYER1_TURN;
	cursorIncrease();
}


void keyboardInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 13:
		if (gameState == MENU_STATE) startGame();
		else changePlayerTurn();
		break;
	case 'r':
		sprintf(lastKeyPressed, "R");
		break;
	case 'a':
		sprintf(lastKeyPressed, "A");
		cursorDecrease();
		break;
	case 's':
		sprintf(lastKeyPressed, "S");
		break;
	case 'd':
		sprintf(lastKeyPressed, "D");
		cursorIncrease();
		break;
	case 'w':
		sprintf(lastKeyPressed, "W");
		break;
	case 'f':
		sprintf(lastKeyPressed, "F");
		glutFullScreen();
		break;
	case 'h':
		sprintf(lastKeyPressed, "H");
		showDebug = !showDebug;
		break;
	}
}

void mouseClickInput(int button, int state, int x, int y)
{
	// ZOOM ALTER
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		if (zoomValue < 70)
		{
			zoomValue += 5;
		}
		else zoomValue = 15.0f;
	}

	// CAMERA MOVEMENT
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			cameraMove = true;
		}
		else if (state == GLUT_UP)
		{
			cameraMove = false;
		}
	}

	// RESET
	if (button == GLUT_MIDDLE_BUTTON)
	{
		zoomValue = 15.0f;
		cameraValueX = 117939.0f;
	}

	glutPostRedisplay();
}

void mouseMoveInput(int x, int y)
{
	mouseX = x;
	mouseY = y;

	// MOUSE X VAR
	if (mouseX > lastMouseX && cameraMove)
	{
		cameraValueX += x;
	}
	else if (mouseX < lastMouseX && cameraMove)
	{
		cameraValueX -= x;
	}

	// MOUSE Y VAR
	if (mouseY > lastMouseY)
	{
		cameraValueY += y;
	}
	else cameraValueY -= y;

	lastMouseX = x;
	lastMouseY = y;

	glutPostRedisplay();
}

void renderText(float x, float y, void* font, const char* string, float red, float green, float blue)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, width, 0.0, height);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(red, green, blue);
	glRasterPos2f(x, y);
	while (*string)
	{
		glutBitmapCharacter(font, *string++);
	}
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void renderDebug()
{
	// MOUSE POS X INFO
	char gameStateText[30];
	sprintf(gameStateText, "GameState: %d", gameState);
	renderText(0, 180, GLUT_BITMAP_TIMES_ROMAN_24, gameStateText, 0, 0, 0);

	// MOUSE POS X INFO
	char mouseXText[30];
	sprintf(mouseXText, "Mouse Pos X: %d", mouseX);
	renderText(0, 150, GLUT_BITMAP_TIMES_ROMAN_24, mouseXText, 0, 0, 0);

	// MOUSE POS X INFO
	char mouseYText[30];
	sprintf(mouseYText, "Mouse Pos Y: %d", mouseY);
	renderText(0, 120, GLUT_BITMAP_TIMES_ROMAN_24, mouseYText, 0, 0, 0);

	// LAST KEY PRESSED
	renderText(0, 90, GLUT_BITMAP_TIMES_ROMAN_24, lastKeyPressed, 0, 0, 0);

	// CAMERA VALUE X INFO
	char cameraValueXText[30];
	sprintf(cameraValueXText, "Camera Value X: %.lf", cameraValueX);
	renderText(0, 60, GLUT_BITMAP_TIMES_ROMAN_24, cameraValueXText, 0, 0, 0);

	// CAMERA VALUE Y INFO
	char cameraValueYText[30];
	sprintf(cameraValueYText, "Camera Value Y: %.lf", cameraValueY);
	renderText(0, 30, GLUT_BITMAP_TIMES_ROMAN_24, cameraValueYText, 0, 0, 0);

	// ZOOM VALUE INFO
	char zoomValueText[30];
	sprintf(zoomValueText, "Zoom Value: %.lf", zoomValue);
	renderText(0, 0, GLUT_BITMAP_TIMES_ROMAN_24, zoomValueText, 0, 0, 0);

}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// CAMERA
	gluLookAt((cos(cameraValueX / 15000) * zoomValue), 10.0f, (sin(cameraValueX / 15000) * zoomValue),
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	// DEBUG INFO
	if (showDebug) renderDebug();

	// BOARD
	glRotatef(rotateAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(-5.5, 0.0, -5);
	board.render();
	
	glutSwapBuffers();
}

void tick(int value)
{
	glutPostRedisplay();
	glutTimerFunc(25, tick, 0);

	printf("%d\n", pieceIndex);
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow(title);

	init();

	glutDisplayFunc(render); // RENDER
	glutReshapeFunc(resize); // RESIZE

	glutKeyboardFunc(keyboardInput); // KEYS INPUT
	glutMouseFunc(mouseClickInput); // CLICKS INPUT
	glutMotionFunc(mouseMoveInput); // MOVE INPUT
	glutTimerFunc(25, tick, 0); // UPDATE

	glutMainLoop();

	return 0;
}