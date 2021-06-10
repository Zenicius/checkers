#pragma once
struct Des
{
	float x, y, z;
};

class Animation
{
	private:
		bool running;
		float destX, destY, destZ;
		float startTime, duration;
	public:
		Animation();
		void start();
		void stop();
		bool isRunning();
		void setDest(float x, float y, float z, float tStart, float duration);
		Des getDest();
		float getStartTime();
		float getDuration();
};

