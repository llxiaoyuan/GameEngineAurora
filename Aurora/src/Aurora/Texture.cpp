#include<Aurora/Texture.hpp>

Texture::Texture() :
	VAO(0), VBO(0), instanceVBO(0), bpp(0), height(0), width(0), rendererID(0), curIndex(0), registered(false), modelMatrices(nullptr)
{
}

Texture::Texture(const std::string& path)
	: rendererID(0), filePath(path), width(0), height(0), bpp(0), VAO(0), VBO(0), instanceVBO(0), curIndex(0), registered(false), modelMatrices(new glm::mat4[defaultMaxMatricesNum])
{
	stbi_set_flip_vertically_on_load(1);
	unsigned char* localBuffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);

	if (localBuffer)
	{
		glGenTextures(1, &rendererID);
		glBindTexture(GL_TEXTURE_2D, rendererID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(localBuffer);

		float positions[] = {0,0,0,0,(float)width,0,1.f,0,(float)width,(float)height,1.f,1.f,0,(float)height,0,1.f};

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

		std::cout << "[" << typeid(*this).name() << "] " << path << " load complete!\n";
	}
	else
	{
		std::cout << "[" << typeid(*this).name() << "] " << path << " load fail!\n";
	}


}

Texture::Texture(unsigned char* buffer, const int& width, const int& height, const int& bpp) :
	rendererID(0), width(width), height(height), bpp(bpp), VAO(0), VBO(0), instanceVBO(0), curIndex(0), registered(false), modelMatrices(new glm::mat4[defaultMaxMatricesNum])
{
	glGenTextures(1, &rendererID);
	glBindTexture(GL_TEXTURE_2D, rendererID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	float positions[] = {0,0,0,0,(float)width ,0 ,1.0f ,0,(float)width ,(float)height ,1.0f,1.0f,0,(float)height,0 ,1.0f};

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

	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Texture::dispose() const
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteTextures(1, &rendererID);
	glDeleteBuffers(1, &instanceVBO);
	if (modelMatrices)
	{
		delete[] modelMatrices;
	}
}

void Texture::bind() const
{
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, rendererID);
}

void Texture::drawInstance() const
{
	glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, curIndex);
}

void Texture::unbind() const
{
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

std::vector<Texture> Texture::loadSplit(const std::string& path, const int& width, const int& height, const int& count)
{
	stbi_set_flip_vertically_on_load(1);
	unsigned char* localBuffer;

	int bitmapWidth;
	int bitmapHeight;
	int bpp;

	localBuffer = stbi_load(path.c_str(), &bitmapWidth, &bitmapHeight, &bpp, 4);

	std::vector<Texture> results;

	for (int i = 0; i < count; i++)
	{
		unsigned char* tempBuffer = new unsigned char[(long long)width * (long long)height * 4];

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				const int pixelIndex = 4 * (y * width + x);
				const int bitmapPixelIndex = 4 * ((y + bitmapHeight - height) * bitmapWidth + x + i * width);
				tempBuffer[pixelIndex] = localBuffer[bitmapPixelIndex];
				tempBuffer[pixelIndex + 1] = localBuffer[bitmapPixelIndex + 1];
				tempBuffer[pixelIndex + 2] = localBuffer[bitmapPixelIndex + 2];
				tempBuffer[pixelIndex + 3] = localBuffer[bitmapPixelIndex + 3];
			}
		}

		results.emplace_back(Texture(tempBuffer, width, height, bpp));

		delete[] tempBuffer;
	}

	std::cout << "[class Texture] Texture Atlas " << path << " Load complete!\n";

	stbi_image_free(localBuffer);

	return results;
}

const int& Texture::getWidth() const
{
	return width;
}

const int& Texture::getHeight() const
{
	return height;
}

void Texture::updateMatrices() const
{
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, curIndex * sizeof(glm::mat4), modelMatrices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Texture::addModel(const glm::mat4& model)
{
	modelMatrices[curIndex++] = model;
}

void Texture::checkIn()
{
	registered = true;
}

void Texture::checkOut()
{
	curIndex = 0;
	registered = false;
}

const bool& Texture::isRegistered() const
{
	return registered;
}

