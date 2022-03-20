#pragma once

#include"Color.hpp"

#include<Aurora/Math.hpp>

class Spark
{
public:

	static constexpr float airDrag = 0.9f;

	static std::list<Spark*>* active;

	static std::list<Spark*>* pool;

	static Spark* add(const float& x,const float& y,const Color& color,const float& angle,const float& speed,const float& life)
	{
		Spark* instance;

		if (!pool->empty())
		{
			instance = pool->back();
			pool->pop_back();
		}
		else
		{
			instance = new Spark();
		}

		instance->x = x;
		instance->y = y;
		instance->preX = x;
		instance->preY = y;
		instance->color = color;
		instance->speedX = sinf(angle) * speed;
		instance->speedY = cosf(angle) * speed;
		instance->life = life;

		active->push_back(instance);
		return instance;
	}

	static void returnInstance(Spark* const spark)
	{
		pool->push_back(spark);
	}

	static void free()
	{
		for (std::list<Spark*>::iterator it = active->begin(); it != active->end(); it++)
		{
			delete* it;
		}

		for (std::list<Spark*>::iterator it = pool->begin(); it != pool->end(); it++)
		{
			delete* it;
		}
	}

	float x;

	float y;

	float preX;

	float preY;

	Color color;

	float speedX;

	float speedY;

	float life;

private:

	Spark() {}

};

std::list<Spark*>* Spark::active = nullptr;

std::list<Spark*>* Spark::pool = nullptr;