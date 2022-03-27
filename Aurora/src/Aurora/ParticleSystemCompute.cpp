#include<Aurora/ParticleSystemCompute.hpp>

ParticleSystemCompute::ParticleSystemCompute(const float& particleSize, const int& maxParticleNumber) :
	particleSize(particleSize), maxParticleNumber(maxParticleNumber), VAO(0), posVBO(0), velVBO(0), colorVBO(0), tbos{ 0,0 },
	shader(Shader::create("res\\shaders\\ShapeShader.shader")),computeShader(Shader::create("res\\shaders\\ParticleCompute.shader"))
{

	glm::mat4 proj = glm::ortho(0.f, (float)Graphics::getWidth(), 0.f, (float)Graphics::getHeight(), -1.f, 1.f);

	shader->bind();
	shader->setMatrix4fv("proj", proj);
	shader->unbind();

	computeShader->create("res\\shaders\\ParticleCompute.shader");
	computeShader->bind();
	dtLocation = computeShader->getUniformLocation("dt");
	stateLocation = computeShader->getUniformLocation("state");
	mousePosLocation = computeShader->getUniformLocation("mousePos");
	computeShader->unbind();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &posVBO);
	glBindBuffer(GL_ARRAY_BUFFER, posVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)* maxParticleNumber, nullptr, GL_DYNAMIC_COPY);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

	glm::vec4* positions = (glm::vec4*)glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(glm::vec4) * maxParticleNumber, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	glm::vec2 center(Graphics::getWidth() / 2, Graphics::getHeight() / 2);

	std::vector<float> thetas(maxParticleNumber);

	std::vector<float> radiuses(maxParticleNumber);

	for (int i = 0; i < maxParticleNumber; i++)
	{
		float theta = Random::Float() * Math::two_pi;
		thetas[i] = theta;
		float radius = Random::Float() * 400.f+100.f;
		radiuses[i] = radius;
		positions[i] = glm::vec4(radius * cosf(theta) + center.x, radius * sinf(theta) + center.y, 0, 1);
	}

	glUnmapBuffer(GL_ARRAY_BUFFER);

	glm::vec4* colors = new glm::vec4[maxParticleNumber];

	for (int i = 0; i < maxParticleNumber; i++)
	{
		colors[i] = glm::vec4(Random::Float(), Random::Float(), Random::Float(), 1);
	}

	glGenBuffers(1, &colorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)* maxParticleNumber, colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	delete[] colors;

	glGenBuffers(1, &velVBO);
	glBindBuffer(GL_ARRAY_BUFFER, velVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)* maxParticleNumber, nullptr, GL_DYNAMIC_COPY);

	glm::vec4* velocities = (glm::vec4*)glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(glm::vec4) * maxParticleNumber, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	for (int i = 0; i < maxParticleNumber; i++)
	{
		glm::vec2 vel = 600.f * glm::vec2(cosf(thetas[i] + Math::half_pi), sinf(thetas[i] + Math::half_pi));
		velocities[i] = glm::vec4(vel, 0, 0);
	}

	glUnmapBuffer(GL_ARRAY_BUFFER);

	glGenTextures(2, tbos);

	glBindTexture(GL_TEXTURE_BUFFER, tbos[0]);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, velVBO);

	glBindTexture(GL_TEXTURE_BUFFER, tbos[1]);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, posVBO);

	glBindTexture(GL_TEXTURE_BUFFER, 0);

}

ParticleSystemCompute::~ParticleSystemCompute()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &posVBO);
	glDeleteBuffers(1, &velVBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteTextures(2, tbos);
	if (shader)
	{
		delete shader;
	}
	if (computeShader)
	{
		delete computeShader;
	}
}

void ParticleSystemCompute::update(const float& dt)
{
	computeShader->bind();

	glBindImageTexture(0, tbos[0], 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

	glBindImageTexture(1, tbos[1], 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

	if (dt >= 0.01f)
	{
		computeShader->setVec1f(dtLocation, 0.012f);
	}
	else
	{
		computeShader->setVec1f(dtLocation, dt);
	}

	glDispatchCompute(10000, 1, 1);

	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

	computeShader->unbind();
}

void ParticleSystemCompute::render()
{
	glPointSize(particleSize);
	shader->bind();
	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, maxParticleNumber);
	glBindVertexArray(0);
	shader->unbind();
}