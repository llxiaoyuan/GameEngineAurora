#pragma once

#include<GameSceneManager.hpp>
#include<Texture.hpp>
#include<iostream>
#include<string>
#include<BitmapFont.hpp>
#include<cstdlib>
#include<ShapeRenderer.hpp>

class FireworkScene :public Scene
{
public:

	FireworkScene(GameSceneManager* gsm) :
		Scene(gsm)
	{
		offset = 200;
		preY = y - 0.01;
	}

	~FireworkScene()
	{
		
	}

	void handleinput() override
	{

	}

	void update(const float& dt) override
	{
		preY = y;
		y += ySpeed;
		ySpeed -= 0.001f;
	}

	void render(SpriteRenderer& renderer) override
	{
		sr.begin();
		sr.drawRCLine(glm::vec2(100, preY), glm::vec2(100, y), 4, 0, 1, 1, 1);
		sr.drawRect(glm::vec2(0, 0), glm::vec2(Graphics::getWidth(), Graphics::getHeight()), 0, 0, 0, 0.07175);
		sr.end();
	}

private:

	int cal = 0;

	float offset;

	ShapeRenderer sr;

	float preY;

	float y = 100;

	float ySpeed = 1;

};