#pragma once
#include <iostream>
#include <stdio.h>
#include <tuple>
#include <array>
#include <vector>
#include "BoardCube.h"
#include "Piece.h"

#define PLAYER1_TURN 1
#define PLAYER1_MOVE 11
#define PLAYER1_JUMP 111
#define PLAYER1_JUMP_MOVE 1111
#define PLAYER1_WON 11111

#define PLAYER2_TURN 2
#define PLAYER2_MOVE 22
#define PLAYER2_WON 222 

class Board
{
	private:
		BoardCube boardCubes[8][8];
		std::vector<Piece> bPieces;
		std::vector<Piece> wPieces;
		std::vector<BoardCube*> availableMoves;
		std::vector<BoardCube*> availableJumps;
	public:
		Board();
		void initBoard();

		void moveCursor(int gameState, int index);
		int countAvailableMoves();
		void clearAvailableMoves(int gameState);
		BoardCube* getAvailableMove(int gameState, int index);
		bool isOffBoard(int row, int column);

		void movePiece(Piece* piece, BoardCube* destination);
		void jumpPiece(int gameState, int index, BoardCube* destination);

		void blackCursor(int gameState, int index);
		int countBlacks(int gameState);
		bool hasBlackPiece(int row, int column);
		bool isValidBlackJump(int srcRow, int srcColumn, int destRow, int destColumn);
		int getBlackMoves(int row, int column);
		int getBJumpMoves(int row, int column);
		std::vector<int> getBJumpPieceIndex();
		int getBJumpPieces();

		void whiteCursor(int index);
		int countWhites();
		bool hasWhitePiece(int row, int column);
		int getWhiteMoves(int row, int column);

		BoardCube* getCube(int row, int column);
		Piece* getWhitePiece(int index);
		Piece* getBlackPiece(int index);
		void deletePiece(int gameState, int row, int column);
		std::tuple<int, int> getCubeBoardPos(BoardCube cube);
		std::tuple<int, int> getPieceBoardPos(Piece piece);

		void render();
};

