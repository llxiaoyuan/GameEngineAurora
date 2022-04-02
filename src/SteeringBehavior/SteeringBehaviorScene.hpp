#pragma once

#include<vector>

#include<Aurora/GameSceneManager.hpp>
#include<Aurora/Rect.hpp>
#include<Aurora/Mouse.hpp>
#include<Aurora/Random.hpp>

#include"Character.hpp"

class SteeringBehaviorScene :public Scene
{
public:

	std::vector<Character> characters;

	TexturePtr arrow;

	SteeringBehaviorScene(GameSceneManager* gsm):
		Scene(gsm),
		arrow(Texture::create("res\\SteeringBehaviorRes\\arrow.png"))
	{
		for (size_t i = 0; i < 1000; i++)
		{
			characters.push_back(Character(glm::vec2(Random::Int() % Graphics::getWidth(), Random::Int() % Graphics::getHeight()), glm::vec2(Random::Int() % 4 - 2, Random::Int() % 4 - 2), 3, 0.1f));
		}
	}

	~SteeringBehaviorScene()
	{
		delete arrow;
	}


	virtual void handleinput() override;


	virtual void update(const float& dt) override;


	virtual void render(SpriteRenderer* const spriteRenderer, ShapeRenderer* const shapeRenderer) override;


};