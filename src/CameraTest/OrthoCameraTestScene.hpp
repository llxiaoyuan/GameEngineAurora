#pragma once

#include<Aurora/GameSceneManager.hpp>
#include<Aurora/OrthoCamera.hpp>


class OrthoCameraTestScene :public Scene
{
public:

	OrthoCameraTestScene(GameSceneManager* gsm) :
		Scene(gsm),
		cam(new OrthoCamera(0, 0))
	{
		x = 0;
		y = 0;
		Mouse::addLeftDownEvent(this, &OrthoCameraTestScene::mouseDown);
	}

	~OrthoCameraTestScene()
	{
		delete cam;
	}

	void handleinput() override
	{

	}

	void update(const float& dt) override
	{
		
	}

	void mouseDown()
	{
		x = Random::Int() % Graphics::getWidth();
		y = Random::Int() % Graphics::getHeight();
	}

	void render(SpriteRenderer* const spriteRenderer, ShapeRenderer* const shapeRenderer) override
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 1, 1, 1);
		shapeRenderer->begin();
		shapeRenderer->drawFilledRect(x, y, 100, 100, 1, 1, 1);
		shapeRenderer->end();
	}

	OrthoCamera* cam;

	int x;
	int y;

};