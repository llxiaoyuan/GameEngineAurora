#include"Graphics.hpp"

float Graphics::deltaTime = 0;

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
