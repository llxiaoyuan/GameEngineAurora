#pragma once

#include<Aurora/GameSceneManager.hpp>

class SampleScene :public Scene
{
public:

	SampleScene(GameSceneManager* gsm) :
		Scene(gsm)
	{
		
	}

	~SampleScene()
	{

	}

	void handleinput() override
	{

	}

	void update(const float& dt) override
	{

	}

	void render(SpriteRenderer* const spriteRenderer, ShapeRenderer* const shapeRenderer) override
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 1, 1, 1);
	}

};