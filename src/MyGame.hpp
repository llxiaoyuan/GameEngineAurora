#pragma once

#include<GameSceneManager.hpp>
#include<Timer.hpp>
#include<glad/glad.h>
#include<iostream>

#include"DinoGame/MyScene.hpp"
#include"DigitalRain/DigitalRainScene.hpp"
#include"FireWorks/FireworkScene.hpp"

class MyGame :public Game
{
public:

	GameSceneManager gsm;
	SpriteRenderer renderer;

	MyGame()
	{
		gsm.push(new MyScene(&gsm));
	}

	~MyGame()
	{
		std::cout << "[" << typeid(*this).name() << "] release!\n";
	}

	std::shared_ptr<Game> clone() override
	{
		return std::make_shared<MyGame>(*this);
	}

	void update(const float& dt) override
	{
		gsm.update(dt);
	}

	void render() override
	{
		gsm.render(renderer);
	}

};