#pragma once
#include "Entity.h"
#include "BoardCube.h"

class Piece: public Entity
{
	public: 
		void movePiece(BoardCube boardCube);
		void render();
};

