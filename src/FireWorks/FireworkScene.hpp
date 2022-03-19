#pragma once

#include<Aurora/GameSceneManager.hpp>
#include<Aurora/Texture.hpp>
#include<Aurora/ShapeRenderer.hpp>
#include<Aurora/BitmapFont.hpp>
#include<iostream>
#include<string>
#include<cstdlib>

#include<Aurora/Mouse.hpp>

class FireworkScene :public Scene
{
public:

	FireworkScene(GameSceneManager* gsm) :
		Scene(gsm)
	{
		
	}

	~FireworkScene()
	{
		
	}

	std::unique_ptr<Scene> clone()
	{
		return std::make_unique<FireworkScene>(*this);
	}

	void handleinput() override
	{

	}

	void update(const float& dt) override
	{
		ang += 0.01f;
	}

	float ang = 0;

	void render(SpriteRenderer* const spriteRenderer,ShapeRenderer* const shapeRenderer) override
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);
		shapeRenderer->begin();
		shapeRenderer->drawRCLine(200, 200, Mouse::getPosition().x, Mouse::getPosition().y, 80, 1, 0, 0);
		shapeRenderer->end();
	}

private:

};