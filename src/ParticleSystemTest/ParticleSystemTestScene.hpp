#pragma once

#include<Aurora/GameSceneManager.hpp>
#include<Aurora/ParticleSystem.hpp>

class ParticleSystemTestScene :public Scene
{
public:

	ParticleSystemTestScene(GameSceneManager* gsm) :
		Scene(gsm), particleSystem(1.5f, 5000)
	{
		
	}

	~ParticleSystemTestScene()
	{
		std::cout << "[class ParticleSystemTestScene] release!\n";
	}

	std::unique_ptr<Scene> clone() override
	{
		return std::make_unique<ParticleSystemTestScene>(*this);
	}

	void handleinput() override
	{

	}

	void update(const float& dt) override
	{
		particleSystem.update(dt);
	}

	void render(SpriteRenderer* const spriteRenderer, ShapeRenderer* const shapeRenderer)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);
		particleSystem.render();

	}

	ParticleSystem particleSystem;

};