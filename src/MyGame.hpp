#pragma once

#include<Aurora/GameSceneManager.hpp>
#include<Aurora/Timer.hpp>
#include<glad/glad.h>
#include<iostream>

#include"DinoGame/MyScene.hpp"
#include"DigitalRain/DigitalRainScene.hpp"
#include"FireWorks/FireworkScene.hpp"
#include"SteeringBehavior/SteeringBehaviorScene.hpp"
#include"FourierDrawing/FourierDrawing.hpp"
#include"LogoInterpreter/LogoInterpreterScene.hpp"
#include"TimeTableCardioid/TimeTableCardioidScene.hpp"
#include"ParticleSystemTest/ParticleSystemTestScene.hpp"
#include"DoomFire/DoomFireScene.hpp"

class MyGame :public Game
{
public:

	GameSceneManager* gsm;
	SpriteRenderer* spriteRenderer;
	ShapeRenderer* shapeRenderer;


	MyGame():
		gsm(GameSceneManager::create()),
		spriteRenderer(SpriteRenderer::create()),
		shapeRenderer(ShapeRenderer::create())
	{
		gsm->push(new DoomFireScene(gsm));
		Graphics::setRecordConfig({ 600ULL,27 });
	}

	~MyGame()
	{
		delete gsm;
		delete spriteRenderer;
		delete shapeRenderer;
		std::cout << "[" << typeid(*this).name() << "] release!\n";
	}

	std::unique_ptr<Game> clone() override
	{
		return std::make_unique<MyGame>(*this);
	}

	void update(const float& dt) override
	{
		gsm->update(dt);
	}

	void render() override
	{
		gsm->render(spriteRenderer,shapeRenderer);
	}

};