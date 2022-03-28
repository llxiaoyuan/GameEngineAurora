#pragma once

#include<Aurora/Random.hpp>

struct ColorRGB
{
	float r;
	float g;
	float b;
};

ColorRGB HSVtoRGB(const float& h, const float& s, const float& v)
{
	float r, g, b, f, p, q, t;
	int i = floorf(h * 6.f);
	f = h * 6 - i;
	p = v * (1 - s);
	q = v * (1 - f * s);
	t = v * (1 - (1 - f) * s);

	switch (i % 6) {
	case 0: r = v, g = t, b = p; break;
	case 1: r = q, g = v, b = p; break;
	case 2: r = p, g = v, b = t; break;
	case 3: r = p, g = q, b = v; break;
	case 4: r = t, g = p, b = v; break;
	case 5: r = v, g = p, b = q; break;
	}

	return { r,g,b };
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
		const ColorRGB c = HSVtoRGB(Random::Float(), 1.0, 1.0);
		r = c.r * 0.15f;
		g = c.g * 0.15f;
		b = c.b * 0.15f;
	}

};

ColorRGB generateColor()
{
	ColorRGB c = HSVtoRGB(Random::Float(), 1.0, 1.0);
	c.r *= 0.15f;
	c.g *= 0.15f;
	c.b *= 0.15f;
	return c;
}