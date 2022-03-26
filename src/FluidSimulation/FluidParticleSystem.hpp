#pragma once

#ifndef _PARTICLE_SYSTEM_HPP_MY_
#define _PARTICLE_SYSTEM_HPP_MY_


#include<Aurora/ParticleSystem.hpp>

class FluidParticleSystem :public ParticleSystem
{
public:

	FluidParticleSystem() :
		ParticleSystem(4.f, Graphics::getWidth()* Graphics::getHeight() / (int)4.f / (int)4.f)
	{
		glm::vec2 startPos(particleSize / 2, particleSize / 2);
		for (int i = 0; i < maxParticleNumber; i++)
		{
			int x = i % (Graphics::getWidth() / (int)particleSize);
			int y = i / (Graphics::getWidth() / (int)particleSize);
			particles[i].pos = glm::vec2(x * particleSize, y * particleSize) + startPos;
			particles[i].color = glm::vec4(1, 1, 1, Random::Float());
		}
	}

	void update(const float& dt) override
	{
		
	}

};

#endif // !_PARTICLE_SYSTEM_HPP_MY_