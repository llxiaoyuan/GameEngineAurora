#include<Aurora/BitmapTexture.hpp>

BitmapTexture::BitmapTexture(const unsigned char* const buffer, const int& width, const int& height, const int& bpp) :
	rendererID(0), width(width), height(height), bpp(bpp), VAO(0), VBO(0), instanceVBO(0), curMatricesNum(0), registered(false), colorVBO(0), modelMatrices(new glm::mat4[defaultMaxMatricesNum]), colors(new glm::vec4[defaultMaxMatricesNum])
{
	glGenTextures(1, &rendererID);
	glBindTexture(GL_TEXTURE_2D, rendererID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	float positions[] = {0,0,0,0,(float)width ,0 ,1.0f ,0,(float)width ,(float)height ,1.0f,1.0f,0,(float)height,0 ,1.0};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), positions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)(2 * sizeof(float)));

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


	glGenBuffers(1, &colorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * defaultMaxMatricesNum, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

BitmapTexture::~BitmapTexture()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteTextures(1, &rendererID);
	glDeleteBuffers(1, &instanceVBO);
	glDeleteBuffers(1, &colorVBO);
	if (modelMatrices)
	{
		delete[] modelMatrices;
	}
	if (colors)
	{
		delete[] colors;
	}
}

void BitmapTexture::bind() const
{
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, rendererID);
}

void BitmapTexture::drawInstance() const
{
	glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, curMatricesNum);
}

void BitmapTexture::unbind() const
{
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void BitmapTexture::update() const
{
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, curMatricesNum * sizeof(glm::mat4), modelMatrices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, curMatricesNum * sizeof(glm::vec4), colors);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BitmapTexture::addModel(const glm::mat4& model)
{
	modelMatrices[curMatricesNum++] = model;
}

void BitmapTexture::addColor(const float& r, const float& g, const float& b, const float& a)
{
	colors[curMatricesNum] = glm::vec4(r, g, b, a);
}

void BitmapTexture::checkIn()
{
	registered = true;
}

void BitmapTexture::checkOut()
{
	curMatricesNum = 0;
	registered = false;
}

const bool& BitmapTexture::isRegistered() const
{
	return registered;
}