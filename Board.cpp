#include "Board.h"

Board::Board()
{
	initBoard();
}

void Board::initBoard()
{
	int k = 0;

	// INIT BLACK AREA AND PIECES
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

				if ((j != 3 && j != 4))
				{
					if (j < 3)
					{
						Piece piece;
						piece.setColor(255.0f, 255.0f, 255.0f);
						piece.setPos(i * 3, 1.0f, j * 1.5);
						piece.setSize(0.5);
						wPieces.push_back(piece);
					}
					else
					{
						Piece piece;
						piece.setColor(0.0f, 0.0f, 0.0f);
						piece.setPos(i * 3, 1.0f, j * 1.5);
						piece.setSize(0.5);
						bPieces.push_back(piece);
					}
				}
			}
			else
			{
				boardCubes[j][i + z].setColor(0.35f, 0.24f, 0.13f);
				boardCubes[j][i + z].setPos((i * 3 + 1.5), 0.0, j * 1.5);
				boardCubes[j][i + z].setSize(1.5f);

				if ((j != 3 && j != 4))
				{
					if (j < 3)
					{
						Piece piece;
						piece.setColor(255.0f, 255.0f, 255.0f);
						piece.setPos((i * 3 + 1.5), 1.0f, j * 1.5);
						piece.setSize(0.5);
						wPieces.push_back(piece);
					}
					else
					{
						Piece piece;
						piece.setColor(0.0f, 0.0f, 0.0f);
						piece.setPos((i * 3 + 1.5), 1.0f, j * 1.5);
						piece.setSize(0.5);
						bPieces.push_back(piece);
					}
				}
			}
			
		}
	}

	// INIT WHITE AREA
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

bool Board::hasBlackPiece(int row, int column)
{
	float x = getCube(row, column)->getPos().x;
	float z = getCube(row, column)->getPos().z;	

	for (Piece& piece : bPieces)
	{
		if (piece.getPos().x == x && piece.getPos().z == z) {
			return true;
		}
	}

	return false;
}

bool Board::hasWhitePiece(int row, int column)
{
	float x = getCube(row, column)->getPos().x;
	float z = getCube(row, column)->getPos().z;

	for (Piece& piece : wPieces)
	{
		if (piece.getPos().x == x && piece.getPos().z == z) {
			return true;
		}
	}

	return false;
}

void Board::getBlackMoves(int row, int column)
{
	availableMoves.clear();
	if (!hasBlackPiece(row, column)) return;

	// CENTER 
	if (row >= 1 && (column >= 1 && column <= 6))
	{
		if (!hasBlackPiece(row - 1, column - 1) && !hasBlackPiece(row - 1, column + 1)) // NO FRINDLY PIECES
		{
			availableMoves.push_back(&boardCubes[row - 1][column - 1]); // LEFT
			availableMoves.push_back(&boardCubes[row - 1][column + 1]); // RIGHT
		}
		else if (hasBlackPiece(row - 1, column - 1) && !hasBlackPiece(row - 1, column + 1)) // FRIENDLY PIECE LEFT
		{
			availableMoves.push_back(&boardCubes[row - 1][column + 1]); // RIGHT
		}
		else if (!hasBlackPiece(row - 1, column - 1) && hasBlackPiece(row - 1, column + 1)) // FRIENDLY PIECE RIGHT
		{
			availableMoves.push_back(&boardCubes[row - 1][column - 1]); // LEFT
		}
	} 
	// EXTREMITIES
	else if (row > 1 && (column == 0 || column == 7)) 
	{
		if (column == 0 && !hasBlackPiece(row - 1, column + 1)) // LEFT EXTREMITY CLEAR RIGHT
		{
			availableMoves.push_back(&boardCubes[row - 1][column + 1]); // RIGHT
		}
		else if (column == 7 && !hasBlackPiece(row - 1, column - 1)) // RIGHT EXTREMITY CLEAR RIGHT
		{
			availableMoves.push_back(&boardCubes[row - 1][column - 1]); // LEFT
		}
	}
}

void Board::movePiece(Piece piece, BoardCube destination)
{
	piece.setPos(destination.getPos().x, 1.0f, destination.getPos().z);
}

BoardCube* Board::getCube(int row, int column)
{
	return &boardCubes[row][column];
}

Piece* Board::getWhitePiece(int index)
{
	return &wPieces.at(index);
}

Piece* Board::getBlackPiece(int index)
{
	return &bPieces.at(index);
}


void Board::render()
{
	// 8x8 BOARD CUBES
	for (auto& rows : boardCubes)
	{
		for (auto& cube : rows)
		{
			cube.render();
		}
	}

	// WHITE PIECES
	for (Piece& piece : wPieces)
	{
		piece.render();

	} 

	// BLACK PIECES
	for (Piece& piece : bPieces)
	{
		piece.render();
	}


	if (!availableMoves.empty())
	{
		for (BoardCube* cube : availableMoves)
		{
			cube->setColor(255.0f, 0.0f, 0.0f);
		}
	}
}