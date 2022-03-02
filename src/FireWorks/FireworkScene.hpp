#pragma once

#include<GameSceneManager.hpp>
#include<Texture.hpp>
#include<iostream>
#include<string>
#include<BitmapFont.hpp>
#include<cstdlib>
#include<ShapeRenderer.hpp>

class FireworkScene :public Scene
{
public:

	FireworkScene(GameSceneManager* gsm) :
		Scene(gsm)
	{
		
	}

	~FireworkScene()
	{
		
	}

	std::shared_ptr<Scene> clone()
	{
		return std::make_shared<std::remove_reference<decltype(*this)>::type>(*this);
	}

	void handleinput() override
	{

	}

	void update(const float& dt) override
	{

	}

	void render(SpriteRenderer& spriteRenderer,ShapeRenderer& shapeRenderer) override
	{
		shapeRenderer.begin();
		shapeRenderer.drawRCLine(glm::vec2(100, 100), glm::vec2(200, 200), 10, 0, 0, 1, 1);
		shapeRenderer.end();
	}

private:

};