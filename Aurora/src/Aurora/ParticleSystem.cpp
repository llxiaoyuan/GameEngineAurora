#include<Aurora/ParticleSystem.hpp>

ParticleSystem::ParticleSystem(const float& particleSize, const int& maxParticleNumber) :
	particles(new Particle[maxParticleNumber]), emitTimer(0.005f), particleSize(particleSize), maxParticleNumber(maxParticleNumber)
{
	shader.create("res\\shaders\\ShapeShader.shader");

	glm::mat4 proj = glm::ortho(0.f, (float)Graphics::getWidth(), 0.f, (float)Graphics::getHeight(), -1.f, 1.f);

	shader.bind();
	shader.setMatrix4fv("proj", proj);
	shader.unbind();

	for (long long i = 0; i < maxParticleNumber; i++)
	{
		particles[i].avtive = false;
		particles[i].pos = glm::vec2(0, 0);
		particles[i].vel = glm::vec2(0, 0);
		particles[i].color = glm::vec4(0, 0, 0, 0);
		particles[i].lifeTime = 0;
		particles[i].lifeTimeRemaining = 0;
	}

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &posVBO);
	glBindBuffer(GL_ARRAY_BUFFER, posVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * maxParticleNumber, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

	glGenBuffers(1, &colorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * maxParticleNumber, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

ParticleSystem::~ParticleSystem()
{
	if (particles)
	{
		delete[] particles;
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &posVBO);
	glDeleteBuffers(1, &colorVBO);
}

void ParticleSystem::update(const float& dt)
{
	if (emitTimer.update())
	{
		emit({});
	}
	for (long long i = 0; i < maxParticleNumber; i++)
	{
		if (!particles[i].avtive)
		{
			continue;
		}
		if (particles[i].lifeTimeRemaining <= 0.0f)
		{
			particles[i].avtive = false;
			particles[i].color.w = 0;
			continue;
		}
		//particles[i].lifeTimeRemaining -= dt;

		if (Mouse::isLeftDown())
		{
			const glm::vec2 center = Mouse::getPosition();

			const glm::vec2 dst = center - particles[i].pos;

			const float length = glm::length(dst);

			const float forceX = 500000 * dst.x / (length * length + 100.f);

			const float forceY = 500000 * dst.y / (length * length + 100.f);

			particles[i].vel += glm::vec2(forceX, forceY) * dt;

		}
		else if (Mouse::isRightDown())
		{
			const glm::vec2 center = Mouse::getPosition();

			const glm::vec2 dst = center - particles[i].pos;

			const float length = glm::length(dst);

			const float forceX = 500000 * dst.x / (length * length + 100.f);

			const float forceY = 500000 * dst.y / (length * length + 100.f);

			particles[i].vel -= glm::vec2(forceX, forceY) * dt;
		}

		particles[i].vel *= 0.99f;

		particles[i].pos += particles[i].vel * dt;

		//particles[i].color.w = particles[i].lifeTimeRemaining / particles[i].lifeTime;
	}
}

void ParticleSystem::render()
{
	glBindBuffer(GL_ARRAY_BUFFER, posVBO);
	for (int i = 0; i < maxParticleNumber; i++)
	{
		glBufferSubData(GL_ARRAY_BUFFER, i * sizeof(glm::vec2), sizeof(glm::vec2), &particles[i].pos);
	}

	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	for (int i = 0; i < maxParticleNumber; i++)
	{
		glBufferSubData(GL_ARRAY_BUFFER, i * sizeof(glm::vec4), sizeof(glm::vec4), &particles[i].color);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glPointSize(particleSize);
	shader.bind();
	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, maxParticleNumber);
	glBindVertexArray(0);
	shader.unbind();
}

void ParticleSystem::emit(const ParticleParams& parameters)
{
	int index = findFirstParticle();
	if (index != -1)
	{
		/*particles[index].avtive = true;
		particles[index].pos = parameters.pos;
		particles[index].vel = parameters.vel;
		particles[index].color = parameters.color;
		particles[index].lifeTime = parameters.lifeTime;
		particles[index].lifeTimeRemaining = parameters.lifeTime;*/
		particles[index].avtive = true;
		particles[index].pos = glm::vec2(Graphics::getWidth() / 2 + 500, Graphics::getHeight() / 2);
		float rads = Random::Float() * Math::two_pi;
		particles[index].vel = glm::vec2(200 * cosf(rads), 200);
		particles[index].lifeTime = 10;
		particles[index].lifeTimeRemaining = 10;
		particles[index].color = glm::vec4(Random::Float(), Random::Float(), Random::Float(), 1);

	}
}

int ParticleSystem::findFirstParticle()
{
	for (int i = 0; i < maxParticleNumber; i++)
	{
		if (!particles[i].avtive)
		{
			return i;
		}
	}
	return -1;
}