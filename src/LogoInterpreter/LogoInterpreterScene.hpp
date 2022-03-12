#pragma once

#include<Aurora/GameSceneManager.hpp>
#include<Aurora/RenderTexture.hpp>

#include<fstream>

#include"Logo.hpp"

class LogoInterpreterScene :public Scene
{
public:

	RenderTexture renderTexture;

	bool finished;

	Logo logo;

	LogoInterpreterScene(GameSceneManager* gsm) :
		Scene(gsm),
		renderTexture(1650, 1050, 1, 1, 1, 1),
		finished(false)
	{
		ifstream file;
		file.open("res\\LogoInterpreterRes\\info.txt");
		std::string commands;
		std::getline(file, commands);
		file.close();
		logo.setText(commands);
		setPos(-300, 300);
	}

	~LogoInterpreterScene()
	{

	}

	std::shared_ptr<Scene> clone()
	{
		return std::make_shared<LogoInterpreterScene>(*this);
	}

	void handleinput() override
	{

	}

	void update(const float& dt) override
	{

	}

	void render(SpriteRenderer& spriteRenderer, ShapeRenderer& shapeRenderer) override
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1, 1, 1, 1);
		if (!finished)
		{
			renderTexture.bind();
			shapeRenderer.begin();
			logo.Draw(shapeRenderer);
			shapeRenderer.end();
			renderTexture.unbind();
			finished = true;
		}
		else
		{
			spriteRenderer.begin();
			spriteRenderer.draw(renderTexture, 0, 0);
			spriteRenderer.end();
		}
	}
};