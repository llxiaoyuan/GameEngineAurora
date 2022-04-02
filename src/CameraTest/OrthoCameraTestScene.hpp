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
		cam->move(-10 * dt, -10 * dt);
		cam->update();
	}

	void render(SpriteRenderer* const spriteRenderer, ShapeRenderer* const shapeRenderer) override
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 1, 1, 1);
		shapeRenderer->setProjMatrix(cam->getProjectionMatrix());
		shapeRenderer->begin();
		const glm::vec3& worldPos = cam->screenToWorld(Mouse::getPosition());
		shapeRenderer->drawFilledRect(worldPos.x, worldPos.y, 100, 100, 1, 1, 1);
		shapeRenderer->end();
	}

	OrthoCamera* cam;

};