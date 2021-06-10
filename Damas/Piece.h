#pragma once
#include "Entity.h"
#include "Animation.h"

class Piece: public Entity
{
	private:
		Animation animation;
		GLUquadric* QUAD = gluNewQuadric();
		bool jump = false;
		bool king = false;
	public: 		
		bool isJumpPiece();
		void setJumpPiece(bool option);
		bool isKing();
		void setKing(bool option);
		void startAnimation(float x, float y, float z, float tStart, float duration);
		Pos getFinalPos();
		void tick(float t);
		void render();
};

