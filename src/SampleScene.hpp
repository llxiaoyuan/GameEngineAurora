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

	}

};