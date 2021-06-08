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

	std::reverse(wPieces.begin(), wPieces.end());
}

void Board::moveCursor(int gameState, int index)
{
	if (gameState == PLAYER1_MOVE || gameState == PLAYER2_MOVE)
	{
		for (BoardCube* cube : availableMoves)
		{
			cube->setColor(0.35f, 0.24f, 0.13f);
		}

		availableMoves.at(index)->setColor(255.0f, 0.0f, 0.0f);
	}
	else if (gameState == PLAYER1_JUMP_MOVE || gameState == PLAYER2_JUMP_MOVE)
	{
		for (BoardCube* cube : availableJumps)
		{
			cube->setColor(0.35f, 0.24f, 0.13f);
		}

		availableJumps.at(index)->setColor(0.0f, 255.0f, 0.0f);
	}
}

int Board::countAvailableMoves()
{
	return availableMoves.size();
}

BoardCube* Board::getAvailableMove(int gameState, int index)
{
	if (gameState == PLAYER1_JUMP_MOVE || gameState == PLAYER2_JUMP_MOVE)
	{
		return availableJumps.at(index);
	}
	else return availableMoves.at(index);
} 

void Board::clearAvailableMoves(int gameState)
{
	for (BoardCube* cube : availableMoves)
	{
		cube->setColor(0.35f, 0.24f, 0.13f);
	}

	for (BoardCube* cube : availableJumps)
	{
		cube->setColor(0.35f, 0.24f, 0.13f);
	}
	
	for (Piece& piece : bPieces)
	{
		piece.setColor(0.0f, 0.0f, 0.0f);
		if (gameState != PLAYER1_JUMP_MOVE) piece.setJumpPiece(false);
	}

	for (Piece& piece : wPieces)
	{
		piece.setColor(255.0f, 255.0f, 255.0f);
		if (gameState != PLAYER2_JUMP_MOVE) piece.setJumpPiece(false);
	}

	availableMoves.clear();
	availableJumps.clear();
}

bool Board::isOffBoard(int row, int column)
{
	if (row > 7 || column > 7 || row < 0 || column < 0)
	{
		return true;
	}
	else return false;
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

bool Board::isValidBlackJump(int srcRow, int srcColumn, int destRow, int destColumn)
{
	if (srcRow > destRow && srcColumn > destColumn && hasWhitePiece(destRow, destColumn)) // GOING FOWARD LEFT
	{
		if (hasWhitePiece(destRow - 1, destColumn - 1) || hasBlackPiece(destRow - 1, destColumn - 1) || 
			isOffBoard(destRow - 1, destColumn - 1))
		{
			return false;
		}
		else return true;
	}
	else if (srcRow > destRow && srcColumn < destColumn && hasWhitePiece(destRow, destColumn)) // GOING FOWARD RIGHT
	{
		if (hasWhitePiece(destRow - 1, destColumn + 1) || hasBlackPiece(destRow - 1, destColumn + 1) ||
			isOffBoard(destRow - 1, destColumn + 1))
		{
			return false;
		}
		else return true;
	}
	else if (srcRow < destRow && srcColumn > destColumn && hasWhitePiece(destRow, destColumn)) // GOING BACKWARDS LEFT
	{
		if (hasWhitePiece(destRow + 1, destColumn - 1) || hasBlackPiece(destRow + 1, destColumn - 1) ||
			isOffBoard(destRow + 1, destColumn - 1))
		{
			return false;
		}
		else return true;
	}
	else if (srcRow < destRow && srcColumn < destColumn && hasWhitePiece(destRow, destColumn)) // GOING BACKWARDS RIGHT
	{
		if (hasWhitePiece(destRow + 1, destColumn + 1) || hasBlackPiece(destRow + 1, destColumn + 1) ||
			isOffBoard(destRow + 1, destColumn + 1))
		{
			return false;
		}
		else return true;
	}

	return false;
}

void Board::blackCursor(int gameState, int index)
{
	if (gameState == PLAYER1_TURN)
	{
		for (Piece& piece : bPieces)
		{
			piece.setColor(0.0f, 0.0f, 0.0f);
		}

		getBlackPiece(index)->setColor(255.0f, 0.0f, 0.0f);
	}
	else if (gameState == PLAYER1_JUMP)
	{
		int pIndex = getBJumpPieceIndex().at(index);

		for (Piece& piece : bPieces)
		{
			piece.setColor(0.0f, 0.0f, 0.0f);
		}

		getBlackPiece(pIndex)->setColor(255.0f, 255.0f, 0.0f);
	}
}

int Board::countBlacks(int gameState)
{
	if (gameState == PLAYER1_TURN)
	{
		return bPieces.size();
	}
	else if (gameState == PLAYER1_JUMP)
	{	
		int count = 0;
		for (Piece& piece : bPieces)
		{
			if (piece.isJumpPiece())
			{
				count++;
			}
		}

		return count;
	}

	return 0;
}

int Board::getBlackMoves(int row, int column)
{
	availableMoves.clear();

	int destRow = row - 1;
	int destLeftColumn = column - 1;
	int destRightColumn = column + 1;
	

	if (!isOffBoard(destRow, destLeftColumn) && 
		!hasBlackPiece(destRow, destLeftColumn) && !hasWhitePiece(destRow, destLeftColumn)) // GOING LEFT
	{
		availableMoves.push_back(&boardCubes[destRow][destLeftColumn]);
	} 
	if (!isOffBoard(destRow, destRightColumn) && 
		!hasBlackPiece(destRow, destRightColumn) && !hasWhitePiece(destRow, destRightColumn)) // GOING RIGHT 
	{
		availableMoves.push_back(&boardCubes[destRow][destRightColumn]);
	}

	return availableMoves.size();
}

std::vector<int> Board::getBJumpPieceIndex()
{
	std::vector<int> indexes;
	for (int i = 0; i < bPieces.size(); i++)
	{
		if (bPieces[i].isJumpPiece())
		{
			indexes.push_back(i);
		}
	}

	return indexes;
}

int Board::getBJumpMoves(int row, int column)
{
	int destRowFoward = row - 1;
	int destRowBackwards = row + 1;
	int destLeftColumn = column - 1;
	int destRightColumn = column + 1;

	// FOWARD LEFT
	if (isValidBlackJump(row, column, destRowFoward, destLeftColumn))
	{
		availableJumps.push_back(&boardCubes[destRowFoward - 1][destLeftColumn - 1]);
	}

	// FOWARD RIGHT
	if (isValidBlackJump(row, column, destRowFoward, destRightColumn))
	{
		availableJumps.push_back(&boardCubes[destRowFoward - 1][destRightColumn + 1]);
	}

	// BACKWARDS LEFT
	if (isValidBlackJump(row, column, destRowBackwards, destLeftColumn))
	{
		availableJumps.push_back(&boardCubes[destRowBackwards + 1][destLeftColumn - 1]);
	}

	// BACKWARDS RIGHT
	if (isValidBlackJump(row, column, destRowBackwards, destRightColumn))
	{
		availableJumps.push_back(&boardCubes[destRowBackwards + 1][destRightColumn + 1]);
	}

	return availableJumps.size();
}

int Board::getBJumpPieces()
{
	int count = 0;
	for (Piece& piece : bPieces)
	{
		int row = std::get<0>(getPieceBoardPos(piece));
		int column = std::get<1>(getPieceBoardPos(piece));

		int destRow = row - 1;
		int destRowBackwards = row + 1;
		int destLeftColumn = column - 1;
		int destRightColumn = column + 1;

		if (isValidBlackJump(row, column, destRow, destLeftColumn)			||		// FOWARD LEFT
			isValidBlackJump(row, column, destRow, destRightColumn)			||      // FOWARD RIGHT
			isValidBlackJump(row, column, destRowBackwards, destLeftColumn) ||		// BACKWARDS LEFT
			isValidBlackJump(row, column, destRowBackwards, destRightColumn))		// BACKWARDS RIGHT
		{
			piece.setJumpPiece(true);
			count++;
		}
	}

	return count;
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

bool Board::isValidWhiteJump(int srcRow, int srcColumn, int destRow, int destColumn)
{
	if (srcRow < destRow && srcColumn < destColumn && hasBlackPiece(destRow, destColumn)) // GOING FOWARD LEFT
	{
		if (hasWhitePiece(destRow + 1, destColumn + 1) || hasBlackPiece(destRow + 1, destColumn + 1) ||
			isOffBoard(destRow + 1, destColumn + 1))
		{
			return false;
		}
		else return true;
	}
	else if (srcRow < destRow && srcColumn > destColumn && hasBlackPiece(destRow, destColumn)) // GOING FOWARD RIGHT
	{
		if (hasWhitePiece(destRow + 1, destColumn - 1) || hasBlackPiece(destRow + 1, destColumn - 1) ||
			isOffBoard(destRow + 1, destColumn - 1))
		{
			return false;
		}
		else return true;
	}
	else if (srcRow > destRow && srcColumn < destColumn && hasBlackPiece(destRow, destColumn)) // GOING BACKWARDS LEFT
	{
		if (hasWhitePiece(destRow - 1, destColumn + 1) || hasBlackPiece(destRow - 1, destColumn + 1) ||
			isOffBoard(destRow - 1, destColumn + 1))
		{
			return false;
		}
		else return true;
	}
	else if (srcRow > destRow && srcColumn > destColumn && hasBlackPiece(destRow, destColumn)) // GOING BACKWARDS RIGHT
	{
		if (hasWhitePiece(destRow - 1, destColumn - 1) || hasBlackPiece(destRow - 1, destColumn - 1) ||
			isOffBoard(destRow - 1, destColumn - 1))
		{
			return false;
		}
		else return true;
	}

	return false;
}

int Board::countWhites(int gameState)
{
	if (gameState == PLAYER2_TURN)
	{
		return wPieces.size();
	}
	else if (gameState == PLAYER2_JUMP)
	{
		int count = 0;
		for (Piece& piece : wPieces)
		{
			if (piece.isJumpPiece())
			{
				count++;
			}
		}

		return count;
	}

	return 0;
}

void Board::whiteCursor(int gameState, int index)
{
	if (gameState == PLAYER2_TURN)
	{
		for (Piece& piece : wPieces)
		{
			piece.setColor(255.0f, 255.0f, 255.0f);
		}

		getWhitePiece(index)->setColor(0.0f, 0.0f, 255.0f);
	}
	else if (gameState == PLAYER2_JUMP)
	{
		int pIndex = getWJumpPieceIndex().at(index);

		for (Piece& piece : wPieces)
		{
			piece.setColor(255.0f, 255.0f, 255.0f);
		}

		getWhitePiece(pIndex)->setColor(255.0f, 0.0f, 255.0f);
	}
}

int Board::getWhiteMoves(int row, int column)
{
	availableMoves.clear();

	int destRow = row + 1;
	int destLeftColumn = column + 1;
	int destRightColumn = column - 1;

	if (!isOffBoard(destRow, destLeftColumn) &&
		!hasBlackPiece(destRow, destLeftColumn) && !hasWhitePiece(destRow, destLeftColumn)) // GOING LEFT
	{
		availableMoves.push_back(&boardCubes[destRow][destLeftColumn]);
	}
	if (!isOffBoard(destRow, destRightColumn) && 
		!hasBlackPiece(destRow, destRightColumn) && !hasWhitePiece(destRow, destRightColumn)) // GOING RIGHT 
	{
		availableMoves.push_back(&boardCubes[destRow][destRightColumn]);
	}

	return availableMoves.size();
}

int Board::getWJumpMoves(int row, int column)
{
	int destRowFoward = row + 1;
	int destRowBackwards = row - 1;
	int destLeftColumn = column + 1;
	int destRightColumn = column - 1;

	// FOWARD LEFT
	if (isValidWhiteJump(row, column, destRowFoward, destLeftColumn))
	{
		availableJumps.push_back(&boardCubes[destRowFoward + 1][destLeftColumn + 1]);
	}

	// FOWARD RIGHT
	if (isValidWhiteJump(row, column, destRowFoward, destRightColumn))
	{
		availableJumps.push_back(&boardCubes[destRowFoward + 1][destRightColumn - 1]);
	}

	// BACKWARDS LEFT
	if (isValidWhiteJump(row, column, destRowBackwards, destLeftColumn))
	{
		availableJumps.push_back(&boardCubes[destRowBackwards - 1][destLeftColumn + 1]);
	}

	// BACKWARDS RIGHT
	if (isValidWhiteJump(row, column, destRowBackwards, destRightColumn))
	{
		availableJumps.push_back(&boardCubes[destRowBackwards - 1][destRightColumn - 1]);
	}

	return availableJumps.size();
}

std::vector<int> Board::getWJumpPieceIndex()
{
	std::vector<int> indexes;
	for (int i = 0; i < wPieces.size(); i++)
	{
		if (wPieces[i].isJumpPiece())
		{
			indexes.push_back(i);
		}
	}

	return indexes;
}

int Board::getWJumpPieces()
{
	int count = 0;
	for (Piece& piece : wPieces)
	{
		int row = std::get<0>(getPieceBoardPos(piece));
		int column = std::get<1>(getPieceBoardPos(piece));

		int destRow = row + 1;
		int destRowBackwards = row - 1;
		int destLeftColumn = column + 1;
		int destRightColumn = column - 1;

		if (isValidWhiteJump(row, column, destRow, destLeftColumn)			||		// FOWARD LEFT 
			isValidWhiteJump(row, column, destRow, destRightColumn)			||		// FOWARD RIGHT
			isValidWhiteJump(row, column, destRowBackwards, destLeftColumn) ||		// BACKWARDS LEFT
			isValidWhiteJump(row, column, destRowBackwards, destRightColumn))		// BACKWARDS RIGHT  
		{
			piece.setJumpPiece(true);
			count++;
		}
	}

	return count;
}

void Board::movePiece(Piece* piece, BoardCube* destination)
{
	piece->setPos(destination->getPos().x, 1.0f, destination->getPos().z);
}

void Board::jumpPiece(int gameState, int index, BoardCube* destination)
{
	int finalIndex;
	Piece* piece = {};
	if (gameState == PLAYER1_JUMP_MOVE)
	{
		finalIndex = getBJumpPieceIndex().at(index);
		piece = getBlackPiece(finalIndex);

		int pRow = std::get<0>(getPieceBoardPos(*piece));
		int pColumn = std::get<1>(getPieceBoardPos(*piece));

		int cRow = std::get<0>(getCubeBoardPos(*destination));
		int cColumn = std::get<1>(getCubeBoardPos(*destination));

		if (pRow > cRow && pColumn < cColumn) // FOWARD RIGHT
		{
			deletePiece(gameState, pRow - 1, pColumn + 1);
		}
		else if (pRow > cRow && pColumn > cColumn) // FOWARD LEFT
		{
			deletePiece(gameState, pRow - 1, pColumn - 1);
		}
		else if(pRow < cRow && pColumn < cColumn) // BACKWARDS RIGHT
		{
			deletePiece(gameState, pRow + 1, pColumn + 1);
		}
		else if (pRow < cRow && pColumn > cColumn) // BACKWARDS LEFT
		{
			deletePiece(gameState, pRow + 1, pColumn - 1);
		}
	}
	else if (gameState == PLAYER2_JUMP_MOVE)
	{
		finalIndex = getWJumpPieceIndex().at(index);
		piece = getWhitePiece(finalIndex);

		int pRow = std::get<0>(getPieceBoardPos(*piece));
		int pColumn = std::get<1>(getPieceBoardPos(*piece));

		int cRow = std::get<0>(getCubeBoardPos(*destination));
		int cColumn = std::get<1>(getCubeBoardPos(*destination));

		if (pRow < cRow && pColumn > cColumn) // FOWARD RIGHT
		{
			deletePiece(gameState, pRow + 1, pColumn - 1);
		}
		else if (pRow < cRow && pColumn < cColumn) // FOWARD LEFT
		{
			deletePiece(gameState, pRow + 1, pColumn + 1);
		}
		else if (pRow > cRow && pColumn > cColumn) // BACKWARDS RIGHT
		{
			deletePiece(gameState, pRow - 1, pColumn - 1);
		}
		else if (pRow > cRow && pColumn < cColumn) // BACKWARDS LEFT
		{
			deletePiece(gameState, pRow - 1, pColumn + 1);
		}
	}

	movePiece(piece, destination);
}

BoardCube* Board::getCube(int row, int column)
{
	return &boardCubes[row][column];
}

Piece* Board::getWhitePiece(int index)
{
	return &wPieces.at(index);
}

void Board::deletePiece(int gameState, int row, int column)
{
	if (gameState == PLAYER1_JUMP_MOVE)
	{
		BoardCube* cube = getCube(row, column);
		for (int i = 0; i < wPieces.size(); i++)
		{
			if (wPieces[i].getPos().x == cube->getPos().x &&
				wPieces[i].getPos().z == cube->getPos().z)
			{
				wPieces.erase(wPieces.begin() + i);
			}
		}
	}
	else if (gameState == PLAYER2_JUMP_MOVE)
	{
		BoardCube* cube = getCube(row, column);
		for (int i = 0; i < bPieces.size(); i++)
		{
			if (bPieces[i].getPos().x == cube->getPos().x &&
				bPieces[i].getPos().z == cube->getPos().z)
			{
				bPieces.erase(bPieces.begin() + i);
			}
		}
	}
}

Piece* Board::getBlackPiece(int index)
{
	return &bPieces.at(index);
}

std::tuple<int, int> Board::getCubeBoardPos(BoardCube cube)
{
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			if (cube.getPos().x == boardCubes[j][i].getPos().x &&
				cube.getPos().z == boardCubes[j][i].getPos().z)
			{
				return std::make_tuple(j, i);
			}
		}
	}

	return std::make_tuple(-1, -1);

}

std::tuple<int, int> Board::getPieceBoardPos(Piece piece)
{
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			if (piece.getPos().x == boardCubes[j][i].getPos().x &&
				piece.getPos().z == boardCubes[j][i].getPos().z)
			{
				return std::make_tuple(j, i);
			}
		}
	}

	return std::make_tuple(-1, -1);

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
}