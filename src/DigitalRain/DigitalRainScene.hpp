#pragma once

#include<GameSceneManager.hpp>
#include<Texture.hpp>
#include<iostream>
#include<string>
#include<BitmapFont.hpp>
#include<cstdlib>

#include"Rain.hpp"

class DigitalRainScene :public Scene
{
public:

	DigitalRainScene(GameSceneManager* gsm) :
		Scene(gsm),
		stride((float)font.getFontSize()),
		font("res\\DigitalRainRes\\Game_0.png", "res\\DigitalRainRes\\Game.fnt",24)
	{
		Rain::stride = font.getFontSize();
		for (size_t i = 0; i < Graphics::getWidth() / stride; i++)
		{
			rains.push_back(Rain((Graphics::getWidth() - Graphics::getWidth() / stride * stride) / 2 + i * stride, rand() % 6 + 8));
		}
	}

	~DigitalRainScene()
	{

	}

	void handleinput() override
	{

	}

	void update(const float& dt) override
	{
		for (int i = 0; i < rains.size(); i++)
		{
			rains[i].update(dt);
			if (rains[i].y + stride * rains[i].len < 0)
			{
				rains[i].re();
			}
		}
	}

	void render(SpriteRenderer& renderer) override
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);
		renderer.begin();
		//renderer.draw(font, "FPS:" + std::to_string(1.f / Graphics::getDeltaTime()), 0, Graphics::getHeight(), 1, 1, 1, 1);
		for (int i = 0; i < rains.size(); i++)
		{
			renderer.draw(font, rains[i].character[0], rains[i].x, rains[i].y, 1, 1, 1, 1);
			for (int j = 1; j < rains[i].character.size(); j++)
			{
				renderer.draw(font, rains[i].character[j], rains[i].x, rains[i].y + stride * j, 0, 1, 0, 1.f - (float)(j - 1) / rains[i].len);
			}
		}
		renderer.end();
	}

private:

	BitmapFont font;

	const float stride;

	std::vector<Rain> rains;

};