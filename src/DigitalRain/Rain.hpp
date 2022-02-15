#pragma once

#include<vector>
#include<SpriteRenderer.hpp>
#include<BitmapFont.hpp>
#include<Graphics.hpp>
#include<cstdlib>

class Rain
{
public:

	std::vector<char> character;

	int len;

	int x, y;

	static float speedFactor;

	static int stride;

	//Speed = 165/timeLimit per sec
	float timeLimit;

	float timeCount;

	Rain(int _x, int _len) :timeLimit(_len / speedFactor), len(_len), character(_len)
	{
		timeCount = 0;
		x = _x;
		y = Graphics::getHeight()+ rand() % (Graphics::getHeight() / stride) * stride;
		for (size_t i = 0; i < _len; i++)
		{
			character[i] = rand() % 94 + 33;
		}

	}

	void re()
	{
		y = Graphics::getHeight() + rand() % (Graphics::getHeight() / stride) * stride;
		len = rand() % 6 + 8;
		timeCount = 0;
		timeLimit = len / speedFactor;
		character = std::vector<char>(len);
		for (size_t i = 0; i < len; i++)
		{
			character[i] = rand() % 94 + 33;
		}
	}

	void update(const float& dt)
	{
		timeCount += dt;
		if (timeCount > timeLimit) {
			for (size_t i = len - 1ULL; i > 0; i--)
			{
				character[i] = character[i - 1ULL];
			}
			character[0] = rand() % 94 + 33;
			timeCount = 0;
			y -= stride;
		}
	}

};

float Rain::speedFactor = 300.f;
int Rain::stride;