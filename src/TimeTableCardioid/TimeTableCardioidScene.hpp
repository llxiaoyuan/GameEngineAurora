#pragma once

#include<Aurora/GameSceneManager.hpp>
#include<Aurora/Graphics.hpp>
#include<Aurora/Timer.hpp>

#include"Cardioid.hpp"

class TimeTableCardioidScene :public Scene
{
public:

	struct Color
	{
		float r;
		float g;
		float b;
	} color;

	Color hsv(int hue, float sat = 1.f, float val = 1.f)
	{
		hue %= 360;
		while (hue < 0) hue += 360;

		if (sat < 0.f) sat = 0.f;
		if (sat > 1.f) sat = 1.f;

		if (val < 0.f) val = 0.f;
		if (val > 1.f) val = 1.f;

		int h = hue / 60;
		float f = float(hue) / 60 - h;
		float p = val * (1.f - sat);
		float q = val * (1.f - sat * f);
		float t = val * (1.f - sat * (1 - f));

		switch (h)
		{
		default:
		case 0:
		case 6: return { val , t , p };
		case 1: return { q , val , p };
		case 2: return { p , val , t };
		case 3: return { p , q , val };
		case 4: return { t , p , val };
		case 5: return { val , p , q };
		}
	}

	Cardioid c;

	size_t d1;

	const size_t d2 = 10000;

	int hue;

	int frameCount;

	const int frameLimit = 6;

	TimeTableCardioidScene(GameSceneManager* gsm) :
		Scene(gsm),
		c(500, glm::vec2(Graphics::getWidth() / 2, Graphics::getHeight() / 2), 360, Pi / 2.0),
		d1(0),
		hue(0),
		color{ 1,1,1 },
		frameCount(0),
		timer(0.004f)
	{
		c.cal();
	}

	~TimeTableCardioidScene()
	{

	}

	void handleinput() override
	{

	}

	void update(const float& dt) override
	{
		while(timer.update())
		{
			d1 += 50ULL;
		}
	}

	void render(SpriteRenderer* const spriteRenderer, ShapeRenderer* const shapeRenderer) override
	{
		color = hsv(hue);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 0, 0, 0);
		shapeRenderer->begin();
		shapeRenderer->drawCircle(c.center[0], c.center[1], c.radius, 1, 1, 1, 1);
		for (size_t i = 0; i < c.points.size(); i++)
		{
			shapeRenderer->drawLine(c.points[i].x, c.points[i].y, c.points[(size_t)(i * d1 / d2) % c.points.size()].x, c.points[(size_t)(i * d1 / d2) % c.points.size()].y, color.r, color.g, color.b, 1);
		}
		shapeRenderer->end();
		if (frameCount++ == frameLimit)
		{
			hue++;
			frameCount = 0;
		}
	}

	Timer timer;
};