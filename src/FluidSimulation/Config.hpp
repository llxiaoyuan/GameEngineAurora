#pragma once

#undef TRANSPARENT

#include<Aurora/Graphics.hpp>

struct Config
{
	const float COLOR_UPDATE_SPEED = 10;
	const float CURL = 30;
	const float DENSITY_DISSIPATION = 1;
	const int DYE_RESOLUTION = 1024;
	const float PRESSURE = 0.8f;
	const int PRESSURE_ITERATIONS = 20;
	const int SIM_RESOLUTION = 256;
	const float SPLAT_FORCE = 6000;
	const float SPLAT_RADIUS = 0.25f;
	const int SUNRAYS_RESOLUTION = 196;
	const float SUNRAYS_WEIGHT = 1;
	const float VELOCITY_DISSIPATION = 0.2f;
};

struct Resolution{
	int width;
	int height;
} getResolution(const float& resolution)
{
	float aspectRatio = (float)Graphics::getWidth() / Graphics::getHeight();

	int min = roundf(resolution);
	int max = roundf(resolution * aspectRatio);

	return { max,min };
}

struct PixelFormat
{
	int internalFormat;
	unsigned int format;
};