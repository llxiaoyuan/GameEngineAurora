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

	const double startX = 0;

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

	FourierDrawing(GameSceneManager* gsm) :
		Scene(gsm),
		epicycles(nullptr),
		renderTexture(1000, 1000)
	{
		std::string filePath = "res\\FourierDrawingRes\\dft_data.json";
		std::ifstream ifs(filePath);
		json dftData = json::parse(ifs);
		ifs.close();

		length = dftData.size();

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

		for (size_t i = 0; i < length; i++)//¼ÆËã³õÊ¼µã
		{
			epicycles[i].set(t);
			preX = x;
			preY = y;
			x += epicycles[i].re;
			y += epicycles[i].im;
		}

		lastPoint = glm::vec2(x, y);

		std::cout << "firstPoint at " << x << " " << y << "\n";

		t += 1.0;

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

		shapeRenderer.drawLine(lastPoint[0], lastPoint[1], x, y, 0, 0, 0);
		shapeRenderer.drawLine(lastPoint[0]+1, lastPoint[1], x+1, y, 0, 0, 0);
		shapeRenderer.drawLine(lastPoint[0], lastPoint[1]+1, x, y+1, 0, 0, 0);
		shapeRenderer.drawLine(lastPoint[0]-1, lastPoint[1], x-1, y, 0, 0, 0);
		shapeRenderer.drawLine(lastPoint[0], lastPoint[1]-1, x, y-1, 0, 0, 0);

		shapeRenderer.end();
		renderTexture.unbind();

		spriteRenderer.begin();
		spriteRenderer.draw(renderTexture, 0, 0);
		spriteRenderer.end();

		lastPoint[0] = x;
		lastPoint[1] = y;

	}

};