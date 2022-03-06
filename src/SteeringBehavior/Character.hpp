#pragma once

#include<glm/glm.hpp>
#include<vector>

class Character
{
public:

	glm::vec2 pos;
	glm::vec2 vel;
	glm::vec2 acc;

	float mSpeed;
	float mForce;

	Character() :mForce(0), mSpeed(0),pos(0,0),vel(0,0),acc(0,0) {}

	Character(const glm::vec2& _pos, const glm::vec2& _vel, const float& _mSpeed, const float& _mForce) :
		pos(_pos), vel(_vel), mSpeed(_mSpeed), mForce(_mForce), acc(0, 0) {}

	void apply(const glm::vec2& v)
	{
		acc += v;
	}

	void flock(const std::vector<Character>& characters)
	{
		glm::vec2 sep = separate(characters);
		glm::vec2 ali = align(characters);
		glm::vec2 coh = cohesion(characters);
		sep *= 1.5L;
		ali *= 1.L;
		coh *= 1.L;
		apply(sep);
		apply(ali);
		apply(coh);
	}

	glm::vec2 separate(const std::vector<Character>& characters)
	{
		float desiredSeparation = 25;
		glm::vec2 steer(0, 0);
		int count = 0;
		for (size_t i = 0; i < characters.size(); i++)
		{
			float d =glm::length(pos - characters[i].pos);
			if ((d > 0) && (d < desiredSeparation))
			{
				glm::vec2 diff = pos - characters[i].pos;
				diff = glm::normalize(diff)/d;
				steer += diff;
				count++;
			}
		}
		if (count > 0)
			steer /= (float)count;
		if (glm::length(steer) > 0)
		{
			steer = steer / glm::length(steer) * mSpeed;
			steer -= vel;
			if (glm::length(steer) > mForce)
			{
				steer = steer / glm::length(steer) * mForce;
			}
		}
		return steer;
	}

	glm::vec2 align(const std::vector<Character>& characters)
	{
		float neighbordist = 50;
		glm::vec2 sum(0, 0);
		int count = 0;
		for (size_t i = 0; i < characters.size(); i++)
		{
			float d = glm::length(pos - characters[i].pos);
			if ((d > 0) && (d < neighbordist))
			{
				sum+= characters[i].vel;
				count++;
			}
		}

		if (count > 0)
		{
			sum = sum / glm::length(sum) * mSpeed;
			glm::vec2 steer = sum - vel;
			if (glm::length(steer) > mForce)
			{
				steer = steer / glm::length(steer) * mForce;
			}
			return steer;
		}
		else
		{
			return glm::vec2(0, 0);
		}
	}

	glm::vec2 cohesion(const std::vector<Character>& characters)
	{
		float neighbordist = 50.L;
		glm::vec2 sum(0, 0);
		int count = 0;
		for (size_t i = 0; i < characters.size(); i++)
		{
			float d = glm::length(pos - characters[i].pos);
			if ((d > 0) && (d < neighbordist))
			{
				sum += characters[i].pos;
				count++;
			}
		}

		if (count > 0)
		{
			sum /= (float)count;
			return seek(sum);
		}
		else
		{
			return glm::vec2(0, 0);
		}
	}

	void update(const float& dt)
	{
		vel = vel + dt * acc;
		if (glm::length(vel) > mSpeed)
		{
			vel = vel / glm::length(vel) * mSpeed;
		}
		pos = pos + dt * vel;
		if (pos.x < -40)
			pos.x = 1960;
		else if (pos.x > 1960)
			pos.x = -40;
		else if (pos.y < -40)
			pos.y = 1120;
		else if (pos.y > 1120)
			pos.y = -40;
		acc=glm::vec2(0, 0);
	}

	glm::vec2 seek(const glm::vec2& target)
	{
		glm::vec2 force = target - pos;
		force = force / glm::length(force) * mSpeed;
		force -= vel;
		if (glm::length(force) > mForce)
		{
			force = force / glm::length(force) * mForce;
		}
		return force;
	}


};