#pragma once

#include<Aurora/GameSceneManager.hpp>
#include<Aurora/RenderTexture.hpp>

#include<glm/glm.hpp>

#include<fstream>
#include<string>

#include"Epicycle.hpp"
#include"json.hpp"

using json = nlohmann::json;

class FourierDrawing :public Scene
{
public:

	const double tPi = 6.28318530717958647692;

	const double startX = 100;

	const double startY = 0;

	double t = 0;

	double x;

	double y;

	double preX;

	double preY;

	Epicycle* epicycles;

	size_t length;

	RenderTexture renderTexture;

	glm::vec2 lastPoint;

	int intervalCount;

	size_t curFrame;

	const int interval;

	FourierDrawing(GameSceneManager* gsm) :
		Scene(gsm),
		epicycles(nullptr),
		renderTexture(1000, 1000),
		intervalCount(0),
		interval(5),
		curFrame(0)
	{
		std::string filePath = "res\\FourierDrawingRes\\dft_data.json";
		std::ifstream ifs(filePath);
		json dftData = json::parse(ifs);
		ifs.close();

		length = dftData.size();

		std::cout << "Length is " << length << "\n";

		double real;
		double imag;
		double radius;

		epicycles = new Epicycle[length];

		const double scale = 1.0;

		for (size_t i = 0; i < length; i++)
		{
			real = dftData[i]["x"].get<double>() * scale;
			imag = dftData[i]["y"].get<double>() * scale;
			radius = sqrt(real * real + imag * imag);
			epicycles[i] = Epicycle(radius, (double)i * tPi / length, atan2(imag, real));
		}

		x = startX;
		y = startY;

		for (size_t i = 0; i < length; i++)//�����ʼ��
		{
			epicycles[i].set(t);
			preX = x;
			preY = y;
			x += epicycles[i].re;
			y += epicycles[i].im;
		}

		lastPoint = glm::vec2(x, y);

		curFrame++;
	}

	~FourierDrawing()
	{
		if (epicycles)
		{
			delete epicycles;
		}
	}

	std::shared_ptr<Scene> clone() override
	{
		return std::make_shared<FourierDrawing>(*this);
	}

	void handleinput() override
	{

	}

	void update(const float& dt) override
	{
		t += 1.0;
	}

	void render(SpriteRenderer& spriteRenderer, ShapeRenderer& shapeRenderer) override
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1, 1, 1, 1);

		x = startX;
		y = startY;

		if (intervalCount++ == interval)
		{
			shapeRenderer.begin();
			for (size_t i = 0; i < length; i++)
			{
				epicycles[i].set(t);
				preX = x;
				preY = y;
				x += epicycles[i].re;
				y += epicycles[i].im;
				shapeRenderer.drawCircle(preX, preY, epicycles[i].length, 0, 0, 0);
				shapeRenderer.drawLine(preX, preY, x, y, 0, 0, 0);
			}
			shapeRenderer.end();

			renderTexture.bind();
			shapeRenderer.begin();
			if (curFrame == length)
			{
				if (glm::length(lastPoint - glm::vec2(x, y)) < 50.f)
				{
					shapeRenderer.drawLine(lastPoint[0], lastPoint[1], x, y, 0, 0, 0);
					shapeRenderer.drawLine(lastPoint[0] + 1, lastPoint[1], x + 1, y, 0, 0, 0);
					shapeRenderer.drawLine(lastPoint[0], lastPoint[1] + 1, x, y + 1, 0, 0, 0);
					shapeRenderer.drawLine(lastPoint[0] - 1, lastPoint[1], x - 1, y, 0, 0, 0);
					shapeRenderer.drawLine(lastPoint[0], lastPoint[1] - 1, x, y - 1, 0, 0, 0);
				}
			}
			else
			{
				shapeRenderer.drawLine(lastPoint[0], lastPoint[1], x, y, 0, 0, 0);
				shapeRenderer.drawLine(lastPoint[0] + 1, lastPoint[1], x + 1, y, 0, 0, 0);
				shapeRenderer.drawLine(lastPoint[0], lastPoint[1] + 1, x, y + 1, 0, 0, 0);
				shapeRenderer.drawLine(lastPoint[0] - 1, lastPoint[1], x - 1, y, 0, 0, 0);
				shapeRenderer.drawLine(lastPoint[0], lastPoint[1] - 1, x, y - 1, 0, 0, 0);
			}
			shapeRenderer.end();
			renderTexture.unbind();

			spriteRenderer.begin();
			spriteRenderer.draw(renderTexture, 0, 0);
			spriteRenderer.end();

			lastPoint[0] = x;
			lastPoint[1] = y;

			intervalCount = 0;
		}
		else
		{
			for (size_t i = 0; i < length; i++)
			{
				epicycles[i].set(t);
				preX = x;
				preY = y;
				x += epicycles[i].re;
				y += epicycles[i].im;
			}

			renderTexture.bind();
			shapeRenderer.begin();
			if (curFrame == length)
			{
				if (glm::length(lastPoint - glm::vec2(x, y)) < 50.f)
				{
					shapeRenderer.drawLine(lastPoint[0], lastPoint[1], x, y, 0, 0, 0);
					shapeRenderer.drawLine(lastPoint[0] + 1, lastPoint[1], x + 1, y, 0, 0, 0);
					shapeRenderer.drawLine(lastPoint[0], lastPoint[1] + 1, x, y + 1, 0, 0, 0);
					shapeRenderer.drawLine(lastPoint[0] - 1, lastPoint[1], x - 1, y, 0, 0, 0);
					shapeRenderer.drawLine(lastPoint[0], lastPoint[1] - 1, x, y - 1, 0, 0, 0);
				}
			}
			else
			{
				shapeRenderer.drawLine(lastPoint[0], lastPoint[1], x, y, 0, 0, 0);
				shapeRenderer.drawLine(lastPoint[0] + 1, lastPoint[1], x + 1, y, 0, 0, 0);
				shapeRenderer.drawLine(lastPoint[0], lastPoint[1] + 1, x, y + 1, 0, 0, 0);
				shapeRenderer.drawLine(lastPoint[0] - 1, lastPoint[1], x - 1, y, 0, 0, 0);
				shapeRenderer.drawLine(lastPoint[0], lastPoint[1] - 1, x, y - 1, 0, 0, 0);
			}
			shapeRenderer.end();
			renderTexture.unbind();

			lastPoint[0] = x;
			lastPoint[1] = y;
		}

		curFrame++;
	}

};