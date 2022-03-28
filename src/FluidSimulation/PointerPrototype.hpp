#pragma once

#include<Aurora/Random.hpp>

struct Color
{
	float r;
	float g;
	float b;
}HSVtoRGB(const float& h, const float& s, const float& v)
{
	float r, g, b, i, f, p, q, t;
	i = floorf(h * 6.f);
	float f = h * 6 - i;
	float p = v * (1 - s);
	float q = v * (1 - f * s);
	float t = v * (1 - (1 - f) * s);

	switch ((int)i % 6) {
	case 0: r = v, g = t, b = p; break;
	case 1: r = q, g = v, b = p; break;
	case 2: r = p, g = v, b = t; break;
	case 3: r = p, g = q, b = v; break;
	case 4: r = t, g = p, b = v; break;
	case 5: r = v, g = p, b = q; break;
	}

	return { r,g,b };
}

Color normalizeColor(const Color& c)
{
	return { c.r / 255.f,c.g / 255.f,c.b / 255.f };
}

struct PointerPrototype
{
	int id = -1;
	float texcoordX = 0;
	float texcoordY = 0;
	float prevTexcoordX = 0;
	float prevTexcoordY = 0;
	float deltaX = 0;
	float deltaY = 0;
	bool down = false;
	bool moved = false;
	float r = 30;
	float g = 0;
	float b = 300;

	void makeColorRandom()
	{
		const Color c = HSVtoRGB(Random::Float(), 1.0, 1.0);
		r = c.r * 0.15f;
		g = c.g * 0.15f;
		b = c.b * 0.15f;
	}

};