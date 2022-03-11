#include<Aurora/RenderTexture.hpp>

RenderTexture::RenderTexture(const int& _width, const int& _height, const int& r, const int& g, const int& b, const int& a) :
	width(_width), height(_height), VAO(0), curIndex(0), instanceVBO(0), registered(false), rendererID(0)
{

	buffer = new unsigned char[width * height * 4];

	if (buffer)
	{

		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				const int pixelIndex = 4 * (i + j * width);
				buffer[pixelIndex] = r;
				buffer[pixelIndex + 1] = g;
				buffer[pixelIndex + 2] = b;
				buffer[pixelIndex + 3] = a;
			}
		}

		glGenTextures(1, &rendererID);
		glBindTexture(GL_TEXTURE_2D, rendererID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		std::vector<float> positions = { 0,0,0,0,(float)width,0,1.f,0,(float)width,(float)height,1.f,1.f,0,(float)height,0,1.f };

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW);
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

		std::cout << "[class RenderTexture] create complete!\n";
	}
	else
	{
		std::cout << "[class RenderTexture] create failed!\n";
	}
}

void RenderTexture::dispose() const
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteTextures(1, &rendererID);
	glDeleteBuffers(1, &instanceVBO);
	delete buffer;
}

const int& RenderTexture::getWidth() const
{
	return width;
}

const int& RenderTexture::getHeight() const
{
	return height;
}

void RenderTexture::bind() const
{
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, rendererID);
}

void RenderTexture::drawInstance() const
{
	glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, curIndex);
}

void RenderTexture::updatePixelData() const
{
	glBindTexture(GL_TEXTURE_2D, rendererID);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderTexture::setPixel(const int& x, const int& y, const int& r, const int& g, const int& b, const int& a)
{
	buffer[4 * (x + y * width)] = r;
	buffer[4 * (x + y * width) + 1] = g;
	buffer[4 * (x + y * width) + 2] = b;
	buffer[4 * (x + y * width) + 3] = a;
}

void RenderTexture::drawLine(int x1, int y1, const int& x2, const int& y2, const int& r, const int& g, const int& b, const int& a)
{
	int dx = x2 - x1;
	// if x1 == x2, then it does not matter what we set here
	int ix((dx > 0) - (dx < 0));

	dx = abs(dx) << 1;

	int dy = y2 - y1;
	// if y1 == y2, then it does not matter what we set here
	int iy((dy > 0) - (dy < 0));
	dy = abs(dy) << 1;

	setPixel(x1, y1, r, g, b, a);

	if (dx >= dy)
	{
		// error may go below zero
		int error(dy - (dx >> 1));

		while (x1 != x2)
		{
			if ((error >= 0) && (error || (ix > 0)))
			{
				error -= dx;
				y1 += iy;
			}
			// else do nothing

			error += dy;
			x1 += ix;

			setPixel(x1, y1, r, g, b, a);
		}
	}
	else
	{
		// error may go below zero
		int error(dx - (dy >> 1));

		while (y1 != y2)
		{
			if ((error >= 0) && (error || (iy > 0)))
			{
				error -= dy;
				x1 += ix;
			}
			// else do nothing

			error += dx;
			y1 += iy;

			setPixel(x1, y1, r, g, b, a);
		}
	}
}

void RenderTexture::unbind() const
{
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderTexture::updateMatrices() const
{
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, curIndex * sizeof(glm::mat4), &modelMatrices[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderTexture::addModel(const glm::mat4& model)
{
	modelMatrices[curIndex++] = model;
}

void RenderTexture::checkIn()
{
	registered = true;
}

void RenderTexture::checkOut()
{
	curIndex = 0;
	registered = false;
}

const bool& RenderTexture::isRegistered() const
{
	return registered;
}
