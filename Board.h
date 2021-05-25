#pragma once
#include "BoardCube.h"

class Board
{
	public:
		BoardCube boardCubes[8][8];

		Board();

		void initBoard();
		void render();
};

