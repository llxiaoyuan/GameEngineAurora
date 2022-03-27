#pragma once

#ifndef _PARTICLE_SYSTEM_WITH_COMPUTE_SHADER_
#define _PARTICLE_SYSTEM_WITH_COMPUTE_SHADER_

#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include"Shader.hpp"
#include"Graphics.hpp"
#include"Random.hpp"
#include"Math.hpp"
#include"Timer.hpp"
#include"Mouse.hpp"

class ParticleSystemCompute
{
public:
	ParticleSystemCompute(const float& particleSize, const int& maxParticleNumber);

	~ParticleSystemCompute();

	void update(const float& dt);

	void render();

	const int maxParticleNumber;

	unsigned int VAO;

	unsigned int posVBO;

	unsigned int velVBO;

	unsigned int colorVBO;

	unsigned int tbos[2];

	Shader* shader;

	Shader* computeShader;

	const float particleSize;

	int dtLocation;

	int stateLocation;

	int mousePosLocation;
};

#endif // !_PARTICLE_SYSTEM_WITH_COMPUTE_SHADER_