#pragma once

#include<Aurora/GameSceneManager.hpp>
#include<Aurora/Texture.hpp>
#include<Aurora/BitmapFont.hpp>
#include<iostream>
#include<string>

#include"Dinosaur.hpp"
#include"Score.hpp"
#include"CloudManager.hpp"
#include"GroundManager.hpp"
#include"ObstacleManager.hpp"

class MyScene :public Scene
{
public:

	MyScene(GameSceneManager* gsm) :
		Scene(gsm),
		font(BitmapFont::create("res\\DinoGameRes\\font\\Game.png", "res\\DinoGameRes\\font\\Game.fnt")),
		isGameEnded(false),
		gameOverTexture(Texture::create("res\\DinoGameRes\\textures\\Gameover.png")),
		gameOverSound(Sound::create("res\\DinoGameRes\\music\\hit.ogg", false))
	{
		dino = new Dinosaur();
		score = 0;
		hiScore = 0;
	}

	~MyScene()
	{
		std::cout << "[" << typeid(*this).name() << "] release!\n";
		delete gameOverTexture;
		delete font;
		delete gameOverSound;
		delete dino;
	}

	std::unique_ptr<Scene> clone()
	{
		return std::make_unique<MyScene>(*this);
	}

	void handleinput() override
	{
		if (isGameEnded && Keyboard::getKeyPress(Keyboard::Enter))
		{
			reStart();
		}
	}

	void update(const float& dt) override
	{
		handleinput();
		if (!isGameEnded)
		{
			dino->update(dt);
			score.update(dt);
			cloudManager.update(dt);
			groundManager.update(dt);
			obstacleManager.update(dt);
			isGameEnded = dinoCollided();
		}
	}

	void render(SpriteRenderer* const spriteRenderer, ShapeRenderer* const shapeRenderer) override
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1, 1, 1, 1);
		spriteRenderer->begin();
		cloudManager.render(spriteRenderer);
		groundManager.render(spriteRenderer);
		obstacleManager.render(spriteRenderer);
		printScore(spriteRenderer);
		dino->render(spriteRenderer);
		if (isGameEnded)
		{
			spriteRenderer->draw(gameOverTexture, Graphics::getWidth() / 2.f, Graphics::getHeight() / 2.f, gameOverTexture->getWidth() / 2.f, gameOverTexture->getHeight() / 2.f);
		}
		spriteRenderer->end();
	}

private:

	bool isGameEnded;

	Sound* gameOverSound;

	ObstacleManager obstacleManager;

	GroundManager groundManager;

	CloudManager cloudManager;

	Texture* gameOverTexture;

	Dinosaur* dino;

	BitmapFont* font;

	Score score;

	int hiScore;

	void printScore(SpriteRenderer* renderer)
	{
		font->draw(renderer, "HI", 660, 490, 0, 1, 1, 1);
		std::string strScore = std::to_string(hiScore);
		float x = 820 - (float)strScore.size() * 20;
		font->draw(renderer, strScore, x, 490);
		if (score.visible)
		{
			strScore = std::to_string(score);
			x = 940 - (float)strScore.size() * 20;
			font->draw(renderer, strScore, x, 490);
		}

	}

	bool dinoCollided()
	{
		for (int i = 0; i < obstacleManager.obstacles.size(); i++)
		{
			if (dino->rect.overLap(obstacleManager.obstacles[i].rect))
			{
				gameEnd();
				return true;
			}
		}
		return false;
	}

	void gameEnd()
	{
		gameOverSound->play();
		dino->collided = true;
	}

	void reStart()
	{
		if (score > hiScore)
		{
			hiScore = score;
		}
		score.isFlashing = false;
		score.flashTime = 6;
		score.flashTimer = 0;
		score.visible = true;
		score = 0;
		isGameEnded = false;
		dino->collided = false;
		dino->isJumping = true;
		dino->speed = glm::vec3(0, 0, 0);
		dino->setPosition(glm::vec3(100, 120, 0));
		obstacleManager.obstacles.clear();
	}

};