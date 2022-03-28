#pragma once

#undef TRANSPARENT

#include<Aurora/Graphics.hpp>

struct Config
{
	float COLOR_UPDATE_SPEED = 10;
	float CURL = 30;
	float DENSITY_DISSIPATION = 1;
	int DYE_RESOLUTION = 1024;
	float PRESSURE = 0.8f;
	int PRESSURE_ITERATIONS = 20;
	int SIM_RESOLUTION = 256;
	float SPLAT_FORCE = 6000;
	float SPLAT_RADIUS = 0.25f;
	int SUNRAYS_RESOLUTION = 196;
	float SUNRAYS_WEIGHT = 1;
	float VELOCITY_DISSIPATION = 0.2f;
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