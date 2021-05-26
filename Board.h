#pragma once

#include "BoardCube.h"
#include "Piece.h"


class Board
{
	private:
		int lastPieceIndex;

	public:
		BoardCube boardCubes[8][8];
		Piece piecesBlack[12];
		Piece piecesWhite[12];
		Board();

		void initBoard();
		void initPieces();
		void render();
};

