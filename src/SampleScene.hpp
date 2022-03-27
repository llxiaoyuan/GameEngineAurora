#pragma once

#include<Aurora/GameSceneManager.hpp>

class SampleScene :public Scene
{
public:

	SampleScene(GameSceneManager* gsm) :
		Scene(gsm)
	{
		std::cout << Utils::File::readAllText("info.txt") << "\n";
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
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 1, 1, 1);
	}

};