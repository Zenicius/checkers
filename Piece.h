#pragma once
#include "Entity.h"
#include "Animation.h"

class Piece: public Entity
{
	private:
		Animation animation;
	public: 
		void tick(float t);
	    void render();
		bool isJumpPiece();
		void setJumpPiece(bool option);
		void startAnimation(float x, float y, float z, float tStart, float duration);
		Pos getFinalPos();
};

