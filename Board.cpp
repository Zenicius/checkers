#include "Board.h"
#include <stdio.h>

Board::Board()
{
	initBoard();
	initPieces();
	
	lastPieceIndex = 0;
}

void Board::initBoard()
{
	int k = 0;

	// INIT BLACK AREA
	for (int j = 0; j < 8; j++)
	{
		k++;
		int z = 0;
		for (int i = 0; i < 4; i++)
		{
			z++;
			if (k % 2 == 0)
			{
				boardCubes[j][i * 2].setColor(0.35f, 0.24f, 0.13f);
				boardCubes[j][i * 2].setPos(i * 3, 0.0f, j * 1.5);
				boardCubes[j][i * 2].setSize(1.5f);
			}
			else
			{
				boardCubes[j][i + z].setColor(0.35f, 0.24f, 0.13f);
				boardCubes[j][i + z].setPos((i * 3 + 1.5), 0.0, j * 1.5);
				boardCubes[j][i + z].setSize(1.5f);
			}
		}
	}

	// ININT WHITE AREA
	for (int j = 0; j < 8; j++)
	{
		k++;
		int z = 0;
		for (int i = 0; i < 4; i++)
		{
			z++;
			if (k % 2 == 0)
			{
				boardCubes[j][i + z].setColor(1.05f, 0.90f, 0.70f);
				boardCubes[j][i + z].setPos((i * 3 + 1.5), 0.0, j * 1.5);
				boardCubes[j][i + z].setSize(1.5f);
			}
			else
			{
				boardCubes[j][i * 2].setColor(1.05f, 0.90f, 0.70f);
				boardCubes[j][i * 2].setPos(i * 3, 0.0f, j * 1.5);
				boardCubes[j][i * 2].setSize(1.5f);
			}
		}
	}
}

void Board::initPieces()
{
	// INIT BLACK PIECES
	int k = 0;
	int c = 0;
	for (float j = 0.0; j < 3; j++)
	{
		k++;
		for (float i = 0.0; i < 4; i++)
		{
			if (k % 2 == 0)
			{
				piecesBlack[c].setColor(0.0f, 0.0f, 0.0f);
				piecesBlack[c].setPos(i * 3, 1.0f, j * 1.5);
				piecesBlack[c].setSize(0.5);

			}
			else
			{
				piecesBlack[c].setColor(0.0f, 0.0f, 0.0f);
				piecesBlack[c].setPos((i * 3 + 1.5), 1.0f, j * 1.5);
				piecesBlack[c].setSize(0.5);
			}
			c++;
		}
	}

	// INIT WHITE PIECES
	c = 0;
	for (float j = 5.0; j < 8; j++)
	{
		k++;
		for (float i = 0.0; i < 4; i++)
		{
			if (k % 2 == 0)
			{
				piecesWhite[c].setColor(255.0f, 255.0f, 255.0f);
				piecesWhite[c].setPos(i * 3, 1.0f, j * 1.5);
				piecesWhite[c].setSize(0.5);

			}
			else
			{
				piecesWhite[c].setColor(255.0f, 255.0f, 255.0f);
				piecesWhite[c].setPos((i * 3 + 1.5), 1.0f, j * 1.5);
				piecesWhite[c].setSize(0.5);
			}
			c++;
		}
	}
}

void Board::render()
{
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			boardCubes[j][i].render();
		}
	}

	for (int i = 0; i < 12; i++)
	{
		piecesBlack[i].render();
		piecesWhite[i].render();
	}
}