#pragma once

#undef TRANSPARENT

struct Config
{
	bool BLOOM = true;
	float BLOOM_INTENSITY = 0.8f;
	int BLOOM_ITERATIONS = 8;
	int BLOOM_RESOLUTION = 256;
	float BLOOM_SOFT_KNEE = 0.7f;
	float BLOOM_THRESHOLD = 0.6f;
	int CAPTURE_RESOLUTION = 512;
	bool COLORFUL = true;
	float COLOR_UPDATE_SPEED = 10;
	float CURL = 30;
	float DENSITY_DISSIPATION = 1;
	int DYE_RESOLUTION = 1024;
	bool PAUSED = false;
	float PRESSURE = 0.8f;
	int PRESSURE_ITERATIONS = 20;
	bool SHADING = true;
	int SIM_RESOLUTION = 256;
	float SPLAT_FORCE = 6000;
	float SPLAT_RADIUS = 0.25f;
	bool SUNRAYS = true;
	int SUNRAYS_RESOLUTION = 196;
	float SUNRAYS_WEIGHT = 1;
	bool TRANSPARENT = false;
	float VELOCITY_DISSIPATION = 0.2f;
};