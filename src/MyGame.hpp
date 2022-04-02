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
#include"FluidSimulation/FluidSimulationScene.hpp"
#include"CameraTest/OrthoCameraTestScene.hpp"

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
		gsm->push(new SteeringBehaviorScene(gsm));
		Graphics::setRecordConfig({ 6000ULL,60 });
	}

	~MyGame()
	{
		delete gsm;
		delete spriteRenderer;
		delete shapeRenderer;
		std::cout << "[" << typeid(*this).name() << "] release!\n";
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