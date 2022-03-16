#pragma once

#include<Aurora/GameSceneManager.hpp>
#include<Aurora/Texture.hpp>

#include"MyParticleSystem.hpp"

class DoomFireScene :public Scene
{
public:

	TexturePtr texture;

	DoomFireScene(GameSceneManager* gsm) :
		Scene(gsm), particleSystem(), texture(Texture::createFromFile("res\\DoomFireRes\\doom.png"))
	{

	}

	~DoomFireScene()
	{
		delete texture;
	}

	std::unique_ptr<Scene> clone()
	{
		return std::make_unique<DoomFireScene>(*this);
	}

	void handleinput() override
	{

	}

	void update(const float& dt) override
	{
		particleSystem.update(dt);
		y += 1.f;
		if (y > 100.f)
		{
			y = 100.f;
		}
	}

	float y = 0;

	void render(SpriteRenderer* const spriteRenderer, ShapeRenderer* const shapeRenderer) override
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);
		spriteRenderer->begin();
		spriteRenderer->draw(texture, (Graphics::getWidth() - texture->getWidth()) / 2, y);
		spriteRenderer->end();
		particleSystem.render();
	}

private:

	MyParticleSystem particleSystem;

};