#include<Aurora/Graphics.hpp>

float Graphics::deltaTime = 0;

float Graphics::frameDuration = 0;

int Graphics::frameCount = 0;

float Graphics::framePerSec = 0;

int Graphics::screenWidth;

int Graphics::screenHeight;

int Graphics::refreshRate;

float Graphics::deltaTimeLimit;

float Graphics::aspectRatio;

Graphics::RecordConfig Graphics::config;

const float& Graphics::getDeltaTime()
{
	return deltaTime;
}

const int& Graphics::getWidth()
{
	return screenWidth;
}

const int& Graphics::getHeight()
{
	return screenHeight;
}

const float& Graphics::getAspectRatio()
{
	return aspectRatio;
}

const float& Graphics::getFPS()
{
	frameDuration += deltaTime;
	frameCount++;
	if (frameDuration > 0.01f)
	{
		framePerSec = frameCount / frameDuration;
		frameCount = 0;
		frameDuration = 0;
	}
	return framePerSec;
}

void Graphics::setRecordConfig(const RecordConfig& _config)
{
	config = _config;
}
