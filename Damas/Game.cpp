/*
* DAMAS
* VINICIUS REIS
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <string.h>
#include <math.h>
#include <tuple>
#include <vector>
#include <GL/glut.h>

#include "Audio.h"
#include "Entity.h"
#include "Board.h"
#include "Piece.h"

// GAME STATES
#define MENU_STATE 0

#define PLAYER1_TURN 1
#define PLAYER1_MOVE 11
#define PLAYER1_JUMP 111
#define PLAYER1_JUMP_MOVE 1111
#define PLAYER1_WON 11111

#define PLAYER2_TURN 2
#define PLAYER2_MOVE 22
#define PLAYER2_JUMP 222
#define PLAYER2_JUMP_MOVE 2222
#define PLAYER2_WON 22222

// WINDOW
std::string title = "Damas";
int width = 1366;
int height = 728;
bool fullScreen = false;

// GAME
int gameState = MENU_STATE;

Board board;
int pieceIndex = -1;
int moveIndex = 0;

// Audio
Audio audio;

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
bool rotateAnimP1 = false;
bool rotateAnimP2 = false;
float rotateAngle = 0.0f;
float cameraValueX = 117939.0f; // CENTER 
float cameraValueY = 0.0f;
float zoomValue = 15.0f;

void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

/*
*
* GAME
*
*/

void cursorIncrease()
{
	if (gameState == PLAYER1_TURN || gameState == PLAYER1_JUMP) 
	{
		if (pieceIndex < board.countBlacks(gameState) - 1)
		{
			pieceIndex++;
			board.blackCursor(gameState, pieceIndex);
		}
	}
	else if (gameState == PLAYER2_TURN || gameState == PLAYER2_JUMP)
	{
		if (pieceIndex < board.countWhites(gameState) - 1)
		{
			pieceIndex++;
			board.whiteCursor(gameState, pieceIndex);
		}
	}
	else if (gameState == PLAYER1_MOVE || gameState == PLAYER2_MOVE || gameState == PLAYER1_JUMP_MOVE) 
	{
		if (moveIndex < board.countAvailableMoves() - 1)
		{
			moveIndex++;
			board.moveCursor(gameState, moveIndex);
		}
	}
}

void cursorDecrease()
{
	if (gameState == PLAYER1_TURN || gameState == PLAYER1_JUMP) 
	{
		if (pieceIndex > 0)
		{
			pieceIndex--;
			board.blackCursor(gameState, pieceIndex);
		}
	}
	else if (gameState == PLAYER2_TURN || gameState == PLAYER2_JUMP) 
	{
		if (pieceIndex > 0)
		{
			pieceIndex--;
			board.whiteCursor(gameState, pieceIndex);
		}
	}
	else if (gameState == PLAYER1_MOVE || gameState == PLAYER2_MOVE || gameState == PLAYER1_JUMP_MOVE) 
	{
		if (moveIndex > 0)
		{
			moveIndex--;
			board.moveCursor(gameState, moveIndex);
		}
	}
}

void changePlayerTurn()
{
	cameraValueX = 117939.0f;
	moveIndex = 0;
	pieceIndex = -1;

	if (gameState == PLAYER2_TURN || gameState == PLAYER2_MOVE ||			
		gameState == PLAYER2_JUMP_MOVE) 
	{ 
		if (board.promoteWhites())										
			audio.playEffect("king");

		board.clearAvailableMoves(gameState);

		if (board.getBJumpPieces() > 0)										
		{
			gameState = PLAYER1_JUMP;
			cursorIncrease();
			rotateAnimP2 = true;
		}
		else													
		{
			gameState = PLAYER1_TURN;
			cursorIncrease();
			rotateAnimP2 = true;
		}
	} 
	else if(gameState == PLAYER1_TURN || gameState == PLAYER1_MOVE ||		
		gameState == PLAYER1_JUMP_MOVE)						
	{
		if (board.promoteBlacks())											
			audio.playEffect("king");			

		board.clearAvailableMoves(gameState);

		if (board.getWJumpPieces() > 0)										
		{
			gameState = PLAYER2_JUMP;
			cursorIncrease();
			rotateAnimP1 = true;
		}
		else																
		{
			board.clearAvailableMoves(gameState);
			gameState = PLAYER2_TURN;
			cursorIncrease();
			rotateAnimP1 = true;
		}
	}
}

void select()
{
	if (gameState == PLAYER1_TURN || gameState == PLAYER1_JUMP)				
	{
		int index = pieceIndex;
		if (gameState == PLAYER1_JUMP) index = board.getBJumpPieceIndex().at(pieceIndex);
		Piece* piece = board.getBlackPiece(index);
		int row = std::get<0>(board.getPieceBoardPos(*piece));
		int column = std::get<1>(board.getPieceBoardPos(*piece));

		if (gameState == PLAYER1_TURN)								
		{
			if (row != -1 && board.getBlackMoves(row, column, piece->isKing()) > 0)
			{
				gameState = PLAYER1_MOVE;
				board.moveCursor(gameState, moveIndex);
			}
		}	
		else if (gameState == PLAYER1_JUMP)									
		{
			if (row != -1 && board.getBJumpMoves(row, column, piece->isKing()) > 0)
			{
				gameState = PLAYER1_JUMP_MOVE;
				board.moveCursor(gameState, moveIndex);
			}
		}
	}
	else if (gameState == PLAYER1_MOVE ||  gameState == PLAYER1_JUMP_MOVE)	
	{
		Piece* piece = board.getBlackPiece(pieceIndex);
		BoardCube* destination = board.getAvailableMove(gameState, moveIndex);
		
		if (gameState == PLAYER1_MOVE)
		{
			board.movePiece(piece, destination);
			audio.playEffect("move");
			changePlayerTurn();
		}
		else if (gameState == PLAYER1_JUMP_MOVE)
		{
			board.jumpPiece(gameState, pieceIndex, destination);
			audio.playEffect("jump");

			int index = board.getBJumpPieceIndex().at(pieceIndex);
			Piece* piece = board.getBlackPiece(index);
			int row = std::get<0>(board.getPieceBoardPos(*piece));
			int column = std::get<1>(board.getPieceBoardPos(*piece));
			
			if (row != -1 && board.getBJumpMoves(row, column, piece->isKing()) > 0)			
			{
				gameState = PLAYER1_JUMP;
			}
			else changePlayerTurn();
		}
	}
	else if (gameState == PLAYER2_TURN || gameState == PLAYER2_JUMP)		
	{
		int index = pieceIndex;
		if (gameState == PLAYER2_JUMP) index = board.getWJumpPieceIndex().at(pieceIndex);
		Piece* piece = board.getWhitePiece(index);
		int row = std::get<0>(board.getPieceBoardPos(*piece));
		int column = std::get<1>(board.getPieceBoardPos(*piece));

		if (gameState == PLAYER2_TURN)
		{
			if (row != -1 && board.getWhiteMoves(row, column, piece->isKing()) > 0)
			{
				gameState = PLAYER2_MOVE;
				board.moveCursor(gameState, moveIndex);
			}
		}
		else if (gameState == PLAYER2_JUMP)
		{
			if (row != -1 && board.getWJumpMoves(row, column, piece->isKing()) > 0)
			{
				gameState = PLAYER2_JUMP_MOVE;
				board.moveCursor(gameState, moveIndex);
			}
		}
	}
	else if (gameState == PLAYER2_MOVE || gameState == PLAYER2_JUMP_MOVE)	 
	{
		Piece* piece = board.getWhitePiece(pieceIndex);
		BoardCube* destination = board.getAvailableMove(gameState, moveIndex);
		
		if (gameState == PLAYER2_MOVE)
		{
			board.movePiece(piece, destination);
			audio.playEffect("move");
			changePlayerTurn();
		}
		else if (gameState == PLAYER2_JUMP_MOVE)
		{
			board.jumpPiece(gameState, pieceIndex, destination);
			audio.playEffect("jump");

			int index = board.getWJumpPieceIndex().at(pieceIndex);
			Piece* piece = board.getWhitePiece(index);
			int row = std::get<0>(board.getPieceBoardPos(*piece));
			int column = std::get<1>(board.getPieceBoardPos(*piece));

			if (row != -1 && board.getWJumpMoves(row, column, piece->isKing()) > 0)			
			{
				gameState = PLAYER2_JUMP;
			}
			else changePlayerTurn();
		}
	}
}

void deselect()
{
	if (gameState == PLAYER1_MOVE || gameState == PLAYER1_JUMP_MOVE)		
	{
		moveIndex = 0;
		board.clearAvailableMoves(gameState);

		if (gameState == PLAYER1_MOVE) gameState = PLAYER1_TURN;
		else if (gameState == PLAYER1_JUMP_MOVE) gameState = PLAYER1_JUMP;

		board.blackCursor(gameState, pieceIndex);
	}
	else if (gameState == PLAYER2_MOVE || gameState == PLAYER2_JUMP_MOVE)	
	{ 
		moveIndex = 0;
		board.clearAvailableMoves(gameState);

		if (gameState == PLAYER2_MOVE) gameState = PLAYER2_TURN;
		else if (gameState == PLAYER2_JUMP_MOVE) gameState = PLAYER2_JUMP;

		board.whiteCursor(gameState, pieceIndex);
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
	// APERTE ENTER
	std::string menuText = "APERTE ENTER PARA INICIAR";
	if(gameState == MENU_STATE)
		renderText(0, 700, GLUT_BITMAP_TIMES_ROMAN_24, menuText.c_str(), 255.0f, 255.0f, 255.0f);

	// GAMESTATE
	std::string gameStateText = "GameState: " + std::to_string(gameState);
	renderText(600, 700, GLUT_BITMAP_TIMES_ROMAN_24, gameStateText.c_str(), 255.0f, 255.0f, 255.0f);

	// LAST KEY PRESSED
	renderText(1150, 15, GLUT_BITMAP_TIMES_ROMAN_24, lastKeyPressed.c_str(), 255.0f, 255.0f, 255.0f);

	// AUDIO VOLUME
	std::string volumeText = "Volume: " + std::to_string(audio.getVolume());
	renderText(0, 180, GLUT_BITMAP_TIMES_ROMAN_24, volumeText.c_str(), 255.0f, 255.0f, 255.0f);

	// COUNT BLACKS
	std::string cBlacksText = "B: " + std::to_string(board.countBlacks(gameState));
	renderText(600, 0, GLUT_BITMAP_TIMES_ROMAN_24, cBlacksText.c_str(), 255.0f, 255.0f, 255.0f);

	// COUNT BLACKS
	std::string cWhitesText = "W: " + std::to_string(board.countWhites(gameState));
	renderText(700, 0, GLUT_BITMAP_TIMES_ROMAN_24, cWhitesText.c_str(), 255.0f, 255.0f, 255.0f);

	// MANDATORY JUMP
	std::string mandatoryText = "Mandatory Jump";
	if (gameState == PLAYER1_JUMP || gameState == PLAYER1_JUMP_MOVE
		|| gameState == PLAYER2_JUMP || gameState == PLAYER2_JUMP_MOVE) 
			renderText(1150, 70, GLUT_BITMAP_TIMES_ROMAN_24, mandatoryText.c_str(), 255.0f, 255.0f, 255.0f);

	// MOUSE POS X INFO
	std::string mouseXText = "Mouse Pos X: " + std::to_string(mouseX);
	renderText(0, 150, GLUT_BITMAP_TIMES_ROMAN_24, mouseXText.c_str(), 255.0f, 255.0f, 255.0f);

	// MOUSE POS X INFO
	std::string mouseYText = "Mouse Pos Y: " + std::to_string(mouseY);
	renderText(0, 120, GLUT_BITMAP_TIMES_ROMAN_24, mouseYText.c_str(), 255.0f, 255.0f, 255.0f);

	// ROTATE ANGLE
	std::string rotateAngleText = "Rotate: " + std::to_string(rotateAngle);
	renderText(0, 90, GLUT_BITMAP_TIMES_ROMAN_24, rotateAngleText.c_str(), 255.0f, 255.0f, 255.0f);

	// CAMERA VALUE X INFO
	std::string cameraValueText = "Camera Value X: " + std::to_string(cameraValueX);
	renderText(0, 60, GLUT_BITMAP_TIMES_ROMAN_24, cameraValueText.c_str(), 255.0f, 255.0f, 255.0f);

	// CAMERA VALUE Y INFO
	std::string cameraValueYText = "Camera Value Y: " + std::to_string(cameraValueY);
	renderText(0, 30, GLUT_BITMAP_TIMES_ROMAN_24, cameraValueYText.c_str(), 255.0f, 255.0f, 255.0f);

	// ZOOM VALUE INFO
	std::string zoomValueText = "Zoom Value " + std::to_string(zoomValue);
	renderText(0, 0, GLUT_BITMAP_TIMES_ROMAN_24, zoomValueText.c_str(), 255.0f, 255.0f, 255.0f);
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
		if(!rotateAnimP1 && !rotateAnimP2) select();
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
	case 'm':
		lastKeyPressed = "M";
		audio.muteMusic();
		break;
	case 45:
		lastKeyPressed = "-";
		audio.decreaseVolume();
		break;
	case 61:
		lastKeyPressed = "+";
		audio.increaseVolume();
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
	glutTimerFunc(1, tick, 0);

	// ROTATE ANIM
	if (rotateAnimP1)
	{
		rotateAngle += 2.5f;
		if (rotateAngle == 180.0f) rotateAnimP1 = false;
	}
	else if (rotateAnimP2)
	{
		rotateAngle -= 2.5f;
		if (rotateAngle == 0.0f) rotateAnimP2 = false;
	}
	
	// UPDATE BOARD
	const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	board.tick(t);

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow(title.c_str());

	init();

	glutDisplayFunc(render); // RENDER
	glutReshapeFunc(resize); // RESIZE

	glutKeyboardFunc(keyboardInput); // KEYS INPUT
	glutMouseFunc(mouseClickInput); // CLICKS INPUT
	glutMotionFunc(mouseMoveInput); // MOVE INPUT
	glutTimerFunc(1, tick, 0); // UPDATE

	glutMainLoop();

	return 0;
}