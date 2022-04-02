#pragma once

#include<Aurora/GameSceneManager.hpp>
#include<Aurora/ParticleSystem.hpp>
#include<Aurora/ParticleSystemCompute.hpp>

class ParticleSystemTestScene :public Scene
{
public:

	ParticleSystemTestScene(GameSceneManager* gsm) :
		Scene(gsm), particleSystemCompute(1.5f, 5000)
	{

	}

	~ParticleSystemTestScene()
	{
		std::cout << "[class ParticleSystemTestScene] release!\n";
	}

	void handleinput() override
	{

	}

	void update(const float& dt) override
	{
		particleSystemCompute.update(dt);
	}

	void render(SpriteRenderer* const spriteRenderer, ShapeRenderer* const shapeRenderer)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);
		particleSystemCompute.render();
	}

	ParticleSystemCompute particleSystemCompute;

};