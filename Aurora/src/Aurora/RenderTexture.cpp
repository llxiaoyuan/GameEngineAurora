#include<Aurora/RenderTexture.hpp>

RenderTexture::RenderTexture(const int& _width, const int& _height, const float& r, const float& g, const float& b, const float& a) :
	fbo(GL::createFBO(width,height,r,g,b,a)), width(_width), height(_height), VAO(0), VBO(0), positionBuffer(0), curMatricesNum(0), registered(false), modelMatrices(new glm::mat4[defaultMaxMatricesNum])
{
	float positions[] = { 0,0,0,0,(float)width,0,1.f,0,(float)width,(float)height,1.f,1.f,0,(float)height,0,1.f };

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), positions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * defaultMaxMatricesNum, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

RenderTexture* RenderTexture::create(const int& width, const int& height, const float& r, const float& g, const float& b, const float& a)
{
	return new RenderTexture(width, height, r, g, b, a);
}

RenderTexture::~RenderTexture()
{
	if (fbo)
	{
		delete fbo;
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &positionBuffer);
	if (modelMatrices)
	{
		delete[] modelMatrices;
	}
}

void RenderTexture::bind() const
{
	fbo->bindFBO();
}

void RenderTexture::unbind() const
{
	fbo->unbindFBO();
}

void RenderTexture::drawInstance() const
{
	glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, curMatricesNum);
}

void RenderTexture::updateMatrices() const
{
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, curMatricesNum * sizeof(glm::mat4), modelMatrices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderTexture::addModel(const glm::mat4& model)
{
	modelMatrices[curMatricesNum++] = model;
}

void RenderTexture::checkIn()
{
	registered = true;
}

void RenderTexture::checkOut()
{
	curMatricesNum = 0;
	registered = false;
}

const bool& RenderTexture::isRegistered() const
{
	return registered;
}
