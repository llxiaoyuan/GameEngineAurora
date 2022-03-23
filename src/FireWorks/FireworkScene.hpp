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
		timer(1.f)
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
		if (timer.update())
		{
			std::cout << "Launch\n";
			(new Shell(getShellConfig(ShellType::crysanthemumShell)))->launch(Mouse::getPosition().x, Mouse::getPosition().y);
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
							Utility::rFloat() * Math::two_pi,
							Utility::rFloat() * star->sparkSpeed * burnRate,
							star->sparkLife * 0.8f + Utility::rFloat() * star->sparkLifeVariation * star->sparkLife
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
		shapeRenderer->begin();
		shapeRenderer->drawFilledRect(0, 0, Graphics::getWidth(), Graphics::getHeight(), 0, 0, 0, 0.175f * speed);

		for (std::list<Star*>::iterator it = Star::active->begin(); it != Star::active->end(); it++)
		{
			Star* const star = *it;
			if (!(star->color == Color::Invisible)&&star->visible)
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
	}

private:

	static constexpr float GRAVITY = 0.9f;

	float speed;

	Timer timer;

	std::list<Star*> starActive;

	std::list<Star*> starPool;

	std::list<Spark*> sparkActive;

	std::list<Spark*> sparkPool;

};