#include "Animation.h"

Animation::Animation()
{
	this->running = false;
	this->destX = 0.0f;
	this->destY = 0.0f;
	this->destZ = 0.0f;
	this->startTime = 0.0f;
	this->duration = 0.0f;
}

void Animation::start()
{
	this->running = true;
}

void Animation::stop()
{
	this->running = false;
}

bool Animation::isRunning()
{
	return this->running;
}

void Animation::setDest(float x, float y, float z, float startTime, float duration)
{
	this->destX = x;
	this->destY = y;
	this->destZ = z;
	this->startTime = startTime;
	this->duration = duration;
}

Des Animation::getDest()
{
	Des pos = { this->destX, this->destY, this->destZ };
	return pos;
}

float Animation::getStartTime()
{
	return this->startTime;
}

float Animation::getDuration()
{
	return this->duration;
}
