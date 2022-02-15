#pragma once

#include<GameSceneManager.hpp>
#include<Texture.hpp>
#include<iostream>
#include<string>
#include<BitmapFont.hpp>

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
		font("res\\DinoGameRes\\font\\Game.png", "res\\DinoGameRes\\font\\Game.fnt"),
		isGameEnded(false),
		gameOverTexture("res\\DinoGameRes\\textures\\Gameover.png")
	{
		score = 0;
		hiScore = 0;
	}

	~MyScene()
	{
		std::cout << "~MyScene\n";
		gameOverTexture.dispose();
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
			dino.update(dt);
			score.update(dt);
			cloudManager.update(dt);
			groundManager.update(dt);
			obstacleManager.update(dt);
			isGameEnded = dinoCollided();
		}
	}

	void render(SpriteRenderer& renderer) override
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1, 1, 1, 1);
		renderer.begin();
		cloudManager.render(renderer);
		groundManager.render(renderer);
		obstacleManager.render(renderer);
		printScore(renderer);
		renderer.draw(dino);
		if (isGameEnded)
		{
			renderer.draw(gameOverTexture, Graphics::getWidth() / 2.f, Graphics::getHeight() / 2.f, gameOverTexture.getWidth() / 2.f, gameOverTexture.getHeight() / 2.f);
		}
		renderer.end();
	}

private:

	bool isGameEnded;

	ObstacleManager obstacleManager;

	GroundManager groundManager;

	CloudManager cloudManager;

	Texture gameOverTexture;

	Dinosaur dino;

	BitmapFont font;

	Score score;

	int hiScore;

	void printScore(SpriteRenderer& renderer)
	{
		renderer.draw(font, "HI", 660, 490, 0, 1, 1, 1);

		std::string strScore = std::to_string(hiScore);
		float x = 820 - (float)strScore.size() * 20;
		renderer.draw(font, strScore, x, 490);

		if (score.visible)
		{
			strScore = std::to_string(score);
			x = 940 - (float)strScore.size() * 20;
			renderer.draw(font, strScore, x, 490);
		}

	}

	bool dinoCollided()
	{
		for (int i = 0; i < obstacleManager.obstacles.size(); i++)
		{
			if (dino.rect.overLap(obstacleManager.obstacles[i].rect))
			{
				gameEnd();
				return true;
			}
		}
		return false;
	}

	void gameEnd()
	{
		Music::play("res\\DinoGameRes\\music\\hit.ogg", false);
		dino.collided = true;
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
		dino.collided = false;
		dino.isJumping = true;
		dino.speed = glm::vec3(0, 0, 0);
		dino.position = glm::vec3(100, 120, 0);
		obstacleManager.obstacles.clear();
	}

};