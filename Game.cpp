/*
* DAMAS
* VINICIUS REIS
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <string>
#include <string.h>
#include <math.h>
#include <tuple>
#include <GL/glut.h>

#include "Entity.h"
#include "Board.h"
#include "Piece.h"

// GAME STATES
#define MENU_STATE 0
#define PLAYER1_TURN 1
#define PLAYER1_MOVE 11
#define PLAYER1_WON 111

#define PLAYER2_TURN 2
#define PLAYER2_MOVE 22
#define PLAYER2_WON 222

// WINDOW
const char* title = "Damas";
int width = 1366;
int height = 728;
bool fullScreen = false;

// GAME
int gameState = MENU_STATE;

Board board;
int pieceIndex = -1;
int moveIndex = 0;

// DEBUG
bool showDebug = true;
std::string lastKeyPressed = "None";

// INPUT
int mouseX = 0;
int lastMouseX = 0;
int mouseY = 0;
int lastMouseY = 0;

// CAMERA
bool cameraMove = false;
float rotateAngle = 0.0f;
bool rotate = false;
float cameraValueX = 117939.0f; // CENTER 
float cameraValueY = 0.0;
float zoomValue = 15.0f;

void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.0f, 0.6f, 0.0f, 1.0f);
}

/*
*
* GAME
*
*/

void changePlayerTurn()
{
	// CHANGE TO OTHER PLAYER VIEW
	cameraValueX = 117939.0f;
	if (rotateAngle == 180.0f) rotateAngle = 0.0f;
	else rotateAngle = 180.0f;

	// RESET INDEX
	moveIndex = 0;
	pieceIndex = 0;

	// CHANGE GAME STATE
	if (gameState == PLAYER2_TURN || gameState == PLAYER2_MOVE)
	{
		gameState = PLAYER1_TURN;
	}
	else if(gameState == PLAYER1_TURN || gameState == PLAYER1_MOVE)
	{
		board.clearAvailableMoves();
		gameState = PLAYER2_TURN;
	}
}

void cursorIncrease()
{
	if (gameState == PLAYER1_TURN)  // SELECTING BLACK PIECE 
	{
		int countB = board.countBlacks() - 1;

		if (pieceIndex < countB)
		{
			pieceIndex++;
			board.blackCursor(pieceIndex);
		}
	}
	else if (gameState == PLAYER1_MOVE) // MOVING BLACK PIECE
	{
		if (moveIndex < board.countAvailableMoves() - 1)
		{
			moveIndex++;
			board.moveCursor(moveIndex);
		}
	}
}

void cursorDecrease()
{
	if (gameState == PLAYER1_TURN) // SELECTING BLACK PIECE
	{
		if (pieceIndex > 0)
		{
			pieceIndex--;
			board.blackCursor(pieceIndex);
		}
	}
	else if (gameState == PLAYER1_MOVE) // MOVING BLACK PIECE
	{
		if (moveIndex > 0)
		{
			moveIndex--;
			board.moveCursor(moveIndex);
		}
	}
}

void select()
{
	if (gameState == PLAYER1_TURN) // SELECTING BLACK PIECE
	{
		Piece* piece = board.getBlackPiece(pieceIndex);
		int row = std::get<0>(board.getPieceBoardPos(*piece));
		int column = std::get<1>(board.getPieceBoardPos(*piece));
		
		if (row != -1 && board.getBlackMoves(row, column) > 0)
		{
			gameState = PLAYER1_MOVE;
			board.moveCursor(moveIndex);
		}
	}
	else if (gameState == PLAYER1_MOVE) // MOVE PIECE
	{
		Piece* piece = board.getBlackPiece(pieceIndex);
		BoardCube* destination = board.getAvailableMove(moveIndex);

		board.movePiece(piece, destination);

		changePlayerTurn();
	}

}

void deselect()
{
	if (gameState == PLAYER1_MOVE)
	{
		board.clearAvailableMoves();
		gameState = PLAYER1_TURN;
	}
}

void startGame()
{
	if (gameState == MENU_STATE)
	{
		gameState = PLAYER1_TURN;
		cursorIncrease();
	}
}

/*
*
* RENDER
*
*/

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
	std::string gameStateText = "GameState: " + std::to_string(gameState);
	renderText(0, 180, GLUT_BITMAP_TIMES_ROMAN_24, gameStateText.c_str(), 0, 0, 0);

	// MOUSE POS X INFO
	std::string mouseXText = "Mouse Pos X: " + std::to_string(mouseX);
	renderText(0, 150, GLUT_BITMAP_TIMES_ROMAN_24, mouseXText.c_str(), 0, 0, 0);

	// MOUSE POS X INFO
	std::string mouseYText = "Mouse Pos Y: " + std::to_string(mouseY);
	renderText(0, 120, GLUT_BITMAP_TIMES_ROMAN_24, mouseYText.c_str(), 0, 0, 0);

	// LAST KEY PRESSED
	renderText(0, 90, GLUT_BITMAP_TIMES_ROMAN_24, lastKeyPressed.c_str(), 0, 0, 0);

	// CAMERA VALUE X INFO
	std::string cameraValueText = "Camera Value X: " + std::to_string(cameraValueX);
	renderText(0, 60, GLUT_BITMAP_TIMES_ROMAN_24, cameraValueText.c_str(), 0, 0, 0);

	// CAMERA VALUE Y INFO
	std::string cameraValueYText = "Camera Value Y: " + std::to_string(cameraValueY);
	renderText(0, 30, GLUT_BITMAP_TIMES_ROMAN_24, cameraValueYText.c_str(), 0, 0, 0);

	// ZOOM VALUE INFO
	std::string zoomValueText = "Zoom Value " + std::to_string(zoomValue);
	renderText(0, 0, GLUT_BITMAP_TIMES_ROMAN_24, zoomValueText.c_str(), 0, 0, 0);
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

/*
*
* SCREEN
*
*/

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200);
}

void toggleFullscreen()
{
	if (fullScreen)
	{
		glutPositionWindow(100, 100);
		glutReshapeWindow(width, height);
		fullScreen = false;
	}
	else
	{
		glutFullScreen();
		fullScreen = true;
	}
}

/*
*
* INPUT
* 
*/

void keyboardInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 13:
		lastKeyPressed = "ENTER";
		startGame();
		break;
	case 8:
		lastKeyPressed = "BACKSPACE";
		deselect();
		break;
	case 32:
		lastKeyPressed = "SPACE";
		select();
		break;
	case 'a':
		lastKeyPressed = "A";
		cursorDecrease();
		break;
	case 'd':
		lastKeyPressed = "D";
		cursorIncrease();
		break;
	case 'f':
		lastKeyPressed = "F";
		toggleFullscreen();
		break;
	case 'h':
		lastKeyPressed = "H";
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

void tick(int value)
{
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