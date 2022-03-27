#pragma once

#include<Aurora/GameSceneManager.hpp>

class FluidSimulationScene :public Scene
{
public:

	FluidSimulationScene(GameSceneManager* gsm) :
		Scene(gsm)
	{

	}

	~FluidSimulationScene()
	{

	}

	std::unique_ptr<Scene> clone()
	{
		return std::make_unique<std::remove_reference<decltype(*this)>::type>(*this);
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
		glClearColor(0, 0, 1, 1);
	}

private:

	void step(const float& dt)
	{
		glDisable(GL_BLEND);

	}

};