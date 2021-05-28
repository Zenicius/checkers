#pragma once
#include <iostream>
#include <stdio.h>
#include <array>
#include <vector>
#include <tuple>
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

		void moveCursor(int index);
		int countAvailableMoves();
		void clearAvailableMoves();
		BoardCube* getAvailableMove(int index);

		void movePiece(Piece* piece, BoardCube* destination);

		bool hasBlackPiece(int row, int column);
		int countBlacks();
		void blackCursor(int index);
		int getBlackMoves(int row, int column);

		bool hasWhitePiece(int row, int column);

		BoardCube* getCube(int row, int column);
		Piece* getWhitePiece(int index);
		Piece* getBlackPiece(int index);
		std::tuple<int, int> getPieceBoardPos(Piece piece);

		void render();
};

