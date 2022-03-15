#pragma once

#ifndef _PARTICLE_SYSTEM_
#define _PARTICLE_SYSTEM_

#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include"Shader.hpp"
#include"Graphics.hpp"
#include"Utility.hpp"
#include"Math.hpp"
#include"Timer.hpp"
#include"Mouse.hpp"

struct ParticleParams
{
	glm::vec2 pos;
	glm::vec2 vel;
	glm::vec4 color;
	float lifeTime;
};

class ParticleSystem
{
public:

	ParticleSystem();

	~ParticleSystem();

	void update(const float& dt);

	void render();

	void emit(const ParticleParams& parameters);

	Timer emitTimer;

	struct Particle
	{
		glm::vec2 pos;
		glm::vec2 vel;
		glm::vec4 color;
		bool avtive;
		float lifeTime;
		float lifeTimeRemaining;
	};

	long long findFirstParticle();

	Particle* particles;

	static constexpr long long maxParticleNumber = 5000;

	unsigned int VAO;

	unsigned int posVBO;

	unsigned int colorVBO;

	Shader shader;

};

#endif // !_PARTICLE_SYSTEM_
