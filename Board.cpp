#include "Board.h"
#include <stdio.h>

Board::Board()
{
	initBoard();
}

void Board::initBoard()
{
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