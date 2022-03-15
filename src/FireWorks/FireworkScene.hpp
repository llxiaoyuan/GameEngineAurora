#pragma once

#include<Aurora/GameSceneManager.hpp>
#include<Aurora/Texture.hpp>
#include<Aurora/ShapeRenderer.hpp>
#include<Aurora/BitmapFont.hpp>
#include<iostream>
#include<string>
#include<cstdlib>

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

	std::shared_ptr<Scene> clone()
	{
		return std::make_shared<std::remove_reference<decltype(*this)>::type>(*this);
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
		glClearColor(1, 1, 1, 1);
		shapeRenderer->begin();
		Rect rect(100, 100, 100, 100);
		shapeRenderer->drawRect(rect, 0, 1, 1, 1);
		shapeRenderer->end();
	}

private:

};