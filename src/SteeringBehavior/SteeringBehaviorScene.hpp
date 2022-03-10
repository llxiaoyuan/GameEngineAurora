#pragma once

#include<vector>

#include<Aurora/GameSceneManager.hpp>
#include<Aurora/Rect.hpp>
#include<Aurora/Mouse.hpp>

#include"Character.hpp"

class SteeringBehaviorScene :public Scene
{
public:

	std::vector<Character> characters;

	Texture arrow;

	SteeringBehaviorScene(GameSceneManager* gsm):
		Scene(gsm),
		arrow("res\\SteeringBehaviorRes\\arrow.png")
	{
		for (size_t i = 0; i < 1000; i++)
		{
			characters.push_back(Character(glm::vec2(rand() % Graphics::getWidth(), rand() % Graphics::getHeight()), glm::vec2(rand() % 4 - 2, rand() % 4 - 2), 3, 0.1f));
		}
	}

	~SteeringBehaviorScene()
	{
		arrow.dispose();
	}

	// Í¨¹ý Scene ¼Ì³Ð
	virtual std::shared_ptr<Scene> clone() override;


	virtual void handleinput() override;


	virtual void update(const float& dt) override;


	virtual void render(SpriteRenderer& spriteRenderer, ShapeRenderer& shapeRenderer) override;


};