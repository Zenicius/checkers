#include "Board.h"
#include <stdio.h>

Board::Board()
{
	initBoard();
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

void Board::render()
{
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			boardCubes[j][i].render();
		}
	}
}