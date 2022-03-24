#pragma once

#include<Aurora/GameSceneManager.hpp>
#include<Aurora/Texture.hpp>
#include<Aurora/ShapeRenderer.hpp>
#include<Aurora/BitmapFont.hpp>
#include<Aurora/Mouse.hpp>

#include<iostream>
#include<string>
#include<cstdlib>
#include<list>

#include"Objects.hpp"

class FireworkScene :public Scene
{
public:

	FireworkScene(GameSceneManager* gsm) :
		Scene(gsm),
		timer(1.f),
		currentSkyColor{ 0.0f,0.0f,0.0f,1.0f },
		texture(RenderTexture::create(1920, 1080, 0, 0, 0, 0))
	{
		Star::active = &starActive;
		Star::pool = &starPool;
		Spark::active = &sparkActive;
		Spark::pool = &sparkPool;
	}

	~FireworkScene()
	{
		Spark::free();
		Star::free();
		delete texture;
	}

	std::unique_ptr<Scene> clone()
	{
		return std::make_unique<FireworkScene>(*this);
	}

	void handleinput() override
	{

	}

	void update(const float& dt) override
	{
		if (Mouse::isLeftDown())
		{
			std::cout << "Launch\n";
			(new Shell(getShellConfig(ShellType::random)))->launch(Mouse::getPosition().x, Mouse::getPosition().y);
		}

		const float width = Graphics::getWidth();
		const float height = Graphics::getHeight();
		speed = 1000.f / 16.6667f * dt;

		const float starDrag = 1.f - (1.f - Star::airDrag) * speed;
		const float starDragHeavy = 1.f - (1.f - Star::airDragHeavy) * speed;
		const float sparkDrag = 1.f - (1.f - Spark::airDrag) * speed;
		const float gAcc = dt * GRAVITY;

		for (std::list<Star*>::iterator it = Star::active->begin(); it != Star::active->end();)
		{
			Star* const star = *it;
			star->life -= dt;

			if (star->life <= 0)
			{
				Star::active->erase(it++);
				Star::returnInstance(star);
			}
			else
			{
				const float burnRate = powf(star->life / star->fullLife, 0.5f);
				const float burnRateInverse = 1.f - burnRate;

				star->preX = star->x;
				star->preY = star->y;

				star->x += star->speedX * speed;
				star->y += star->speedY * speed;

				if (!star->heavy)
				{
					star->speedX *= starDrag;
					star->speedY *= starDrag;
				}
				else
				{
					star->speedX *= starDragHeavy;
					star->speedY *= starDragHeavy;
				}

				star->speedY -= gAcc;

				if (star->spinRadius)
				{
					star->spinAngle += star->spinSpeed * speed;
					star->x += sinf(star->spinAngle) * star->spinRadius * speed;
					star->y += cosf(star->spinAngle) * star->spinRadius * speed;
				}

				if (star->sparkFreq)
				{
					star->sparkTimer -= dt;
					while (star->sparkTimer < 0)
					{
						star->sparkTimer += star->sparkFreq * 0.75f + star->sparkFreq * burnRateInverse * 4.f;
						Spark::add(
							star->x,
							star->y,
							star->sparkColor,
							Random::Float() * Math::two_pi,
							Random::Float() * star->sparkSpeed * burnRate,
							star->sparkLife * 0.8f + Random::Float() * star->sparkLifeVariation * star->sparkLife
						);
					}
				}

				if (star->life < star->transitionTime)
				{
					if (star->haveSecondColor && !star->colorChanged)
					{
						star->colorChanged = true;
						star->color = star->secondColor;

						int r = star->color.r * 255;
						int g = star->color.g * 255;
						int b = star->color.b * 255;
						if (r == 0 && g == 0 && b == 0)
						{
							star->sparkFreq = 0;
						}
					}

					if (star->strobe)
					{
						star->visible = ((int)floorf(star->life / star->strobeFreq) % 3 == 0);
					}
				}
				it++;
			}
		}

		for (std::list<Spark*>::iterator it = Spark::active->begin(); it != Spark::active->end();)
		{
			Spark* const spark = *it;
			spark->life -= dt;
			if (spark->life <= 0)
			{
				Spark::active->erase(it++);
				Spark::returnInstance(spark);
			}
			else
			{
				spark->preX = spark->x;
				spark->preY = spark->y;
				spark->x += spark->speedX * speed;
				spark->y += spark->speedY * speed;
				spark->speedX *= sparkDrag;
				spark->speedY *= sparkDrag;
				spark->speedY -= gAcc;
				it++;
			}
		}

	}

	void render(SpriteRenderer* const spriteRenderer, ShapeRenderer* const shapeRenderer) override
	{
		colorSky();
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(currentSkyColor.r / 255.f, currentSkyColor.g / 255.f, currentSkyColor.b / 255.f, 1.f);

		texture->bind();
		shapeRenderer->begin();
		shapeRenderer->drawFilledRect(0, 0, Graphics::getWidth(), Graphics::getHeight(), 0, 0, 0, 0.175f * speed);

		for (std::list<Star*>::iterator it = Star::active->begin(); it != Star::active->end(); it++)
		{
			Star* const star = *it;
			if (!(star->color == Color::Invisible) && star->visible)
			{
				shapeRenderer->drawRCLine(star->preX, star->preY, star->x, star->y, Star::drawWidth, star->color.r, star->color.g, star->color.b, star->color.a);
				shapeRenderer->drawLine(star->x - star->speedX * 1.6f, star->y - star->speedY * 1.6f, star->x, star->y, 1, 1, 1, 1);
			}
		}

		for (std::list<Spark*>::iterator it = Spark::active->begin(); it != Spark::active->end(); it++)
		{
			Spark* const spark = *it;
			shapeRenderer->drawLine(spark->preX, spark->preY, spark->x, spark->y, spark->color.r, spark->color.g, spark->color.b, spark->color.a);
		}

		shapeRenderer->end();
		texture->unbind();

		spriteRenderer->begin();
		spriteRenderer->draw(texture, 0, 0);
		spriteRenderer->end();
	}

	void colorSky()
	{
		const float maxSkySaturation = 30.f;
		const int maxStarCount = 500;
		int totalStarCount = 0;

		targetSkyColor.r = 0;
		targetSkyColor.g = 0;
		targetSkyColor.b = 0;

		for (std::list<Star*>::iterator it = Star::active->begin(); it != Star::active->end(); it++)
		{
			Star* const star = *it;
			totalStarCount++;
			targetSkyColor.r += star->color.r * 255.f;
			targetSkyColor.g += star->color.g * 255.f;
			targetSkyColor.b += star->color.b * 255.f;
		}

		const float intensity = powf(fminf(1, (float)totalStarCount / maxStarCount), 0.3f);

		float maxColorComponent = 1.f;

		if (targetSkyColor.r > maxColorComponent)
		{
			maxColorComponent = targetSkyColor.r;
		}

		if (targetSkyColor.g > maxColorComponent)
		{
			maxColorComponent = targetSkyColor.g;
		}

		if (targetSkyColor.b > maxColorComponent)
		{
			maxColorComponent = targetSkyColor.b;
		}

		targetSkyColor.r = targetSkyColor.r / maxColorComponent * maxSkySaturation * intensity;
		targetSkyColor.g = targetSkyColor.g / maxColorComponent * maxSkySaturation * intensity;
		targetSkyColor.b = targetSkyColor.b / maxColorComponent * maxSkySaturation * intensity;

		const float colorChange = 10;

		currentSkyColor.r += (targetSkyColor.r - currentSkyColor.r) / colorChange * speed;
		currentSkyColor.g += (targetSkyColor.g - currentSkyColor.g) / colorChange * speed;
		currentSkyColor.b += (targetSkyColor.b - currentSkyColor.b) / colorChange * speed;

	}

private:

	static constexpr float GRAVITY = 0.9f;

	Color currentSkyColor;

	Color targetSkyColor;

	float speed;

	Timer timer;

	std::list<Star*> starActive;

	std::list<Star*> starPool;

	std::list<Spark*> sparkActive;

	std::list<Spark*> sparkPool;

	RenderTexture* texture;

};