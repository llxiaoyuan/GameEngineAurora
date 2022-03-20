#pragma once

#ifndef _STAR_HPP_
#define _STAR_HPP_

#include<Aurora/Math.hpp>
#include<Aurora/Utility.hpp>

#include"Color.hpp"

#include<iostream>

#include<List>

class Star
{
public:

	static constexpr float drawWidth = 1.5f;

	static constexpr float airDrag = 0.98f;

	static constexpr float airDragHeavy = 0.992f;

	static std::list<Star*>* active;

	static std::list<Star*>* pool;

	static Star* add(const float& x, const float& y, const Color& color, const float& angle, const float& speed, const float& life, const float& speedOffX = 0.f, const float& speedOffY = 0.f)
	{
		Star* instance;

		if (!pool->empty())
		{
			instance = pool->back();
			pool->pop_back();
		}
		else
		{
			instance = new Star();
		}

		instance->visible = true;
		instance->heavy = false;
		instance->x = x;
		instance->y = y;
		instance->preX = x;
		instance->preY = y;
		instance->color = color;
		instance->speedX = sinf(angle) * speed + (speedOffX || 0);
		instance->speedY = cosf(angle) * speed + (speedOffY || 0);
		instance->life = life;
		instance->fullLife = life;
		instance->spinAngle = Utility::rFloat() * Math::two_pi;
		instance->spinSpeed = 0.8f;
		instance->spinRadius = 0;
		instance->sparkFreq = 0;
		instance->sparkSpeed = 1;
		instance->sparkTimer = 0;
		instance->sparkColor = color;
		instance->sparkLife = 0.75f;
		instance->sparkLifeVariation = 0.25f;
		instance->strobe = false;
		instance->haveSecondColor = false;
		instance->transitionTime = 0;
		instance->colorChanged = false;
		instance->strobeFreq = 0;
		instance->onDeath = nullptr;

		active->push_back(instance);
		return instance;
	}

	static void returnInstance(Star* const star)
	{
		pool->push_back(star);
	}

	static void free()
	{
		for (std::list<Star*>::iterator it = active->begin(); it != active->end(); it++)
		{
			delete* it;
		}

		for (std::list<Star*>::iterator it = pool->begin(); it != pool->end(); it++)
		{
			delete* it;
		}
	}

	bool visible;

	bool heavy;

	float x;

	float y;

	float preX;

	float preY;

	Color color;

	Color secondColor;

	bool haveSecondColor;

	bool colorChanged;

	float speedX;

	float speedY;

	float life;

	float fullLife;

	float transitionTime;

	float spinAngle;

	float spinSpeed;

	float spinRadius;

	float sparkFreq;

	float sparkSpeed;

	float sparkTimer;

	float sparkLife;

	float sparkLifeVariation;

	Color sparkColor;

	bool strobe;

	float strobeFreq;

	bool (*onDeath)(Star* const star);

private:

	Star() {}

};

std::list<Star*>* Star::active = nullptr;

std::list<Star*>* Star::pool = nullptr;


#endif // !_STAR_HPP_