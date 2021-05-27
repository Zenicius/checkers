#pragma once
#include <iostream>
#include <stdio.h>
#include <array>
#include <vector>
#include "BoardCube.h"
#include "Piece.h"

class Board
{
	private:
		BoardCube boardCubes[8][8];
		std::vector<Piece> bPieces;
		std::vector<Piece> wPieces;
		std::vector<BoardCube*> availableMoves;
	public:
		Board();
		void initBoard();

		void movePiece(Piece piece, BoardCube destination);

		bool hasBlackPiece(int row, int column);
		void getBlackMoves(int row, int column);

		bool hasWhitePiece(int row, int column);

		BoardCube* getCube(int row, int column);
		Piece* getWhitePiece(int index);
		Piece* getBlackPiece(int index);

		void render();
};

