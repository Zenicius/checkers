#pragma once
#include "Entity.h"

class Piece: public Entity
{
	public: 
		void render();
		bool isJumpPiece();
		void setJumpPiece(bool option);
};

