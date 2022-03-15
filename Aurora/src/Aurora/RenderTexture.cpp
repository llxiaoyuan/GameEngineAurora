#include<Aurora/RenderTexture.hpp>

RenderTexture::RenderTexture(const int& _width, const int& _height, const float& r, const float& g, const float& b, const float& a) :
	FBO(0), width(_width), height(_height), VAO(0), VBO(0), instanceVBO(0), texColorBuffer(0), curMatricesNum(0), registered(false), modelMatrices(new glm::mat4[defaultMaxMatricesNum])
{
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

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

	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
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
	glDeleteFramebuffers(1, &FBO);
	glDeleteTextures(1, &texColorBuffer);
	glDeleteRenderbuffers(1, &rbo);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &instanceVBO);
	if (modelMatrices)
	{
		delete[] modelMatrices;
	}
}

void RenderTexture::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void RenderTexture::unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTexture::drawInstance() const
{
	glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, curMatricesNum);
}

void RenderTexture::updateMatrices() const
{
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
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
