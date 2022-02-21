#pragma once

#include<GameSceneManager.hpp>
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
		gsm.push(new DigitalRainScene(&gsm));
	}

	~MyGame()
	{
		
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