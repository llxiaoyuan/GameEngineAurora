#include"Graphics.hpp"

float Graphics::deltaTime = 0;

float Graphics::frameDuration = 0;

int Graphics::frameCount = 0;

float Graphics::FPS = 0;

 int Graphics::screenWidth;

int Graphics::screenHeight;

const float& Graphics::getDeltaTime()
{
	return deltaTime;
}

void Graphics::setDeltaTime(const float& dt)
{
	deltaTime = dt;
}

const int& Graphics::getWidth()
{
	return screenWidth;
}

const int& Graphics::getHeight()
{
	return screenHeight;
}

const float& Graphics::getFPS()
{
	frameDuration += deltaTime;
	frameCount++;
	if (frameDuration > 0.1f)
	{
		FPS = frameCount / frameDuration;
		frameCount = 0;
		frameDuration = 0;
	}
	return FPS;
}
