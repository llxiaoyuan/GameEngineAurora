#include"Texture.hpp"

Texture::Texture()
{
}

Texture::Texture(const std::string& path)
	:rendererID(0), filePath(path), width(0), height(0), bpp(0), VAO(0), VBO(0)
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

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		std::cout << "["<<typeid(*this).name()<<"] " << path << " load complete!\n";
	}
	else
	{
		std::cout << "[" << typeid(*this).name() << "] " << path << " load fail!\n";
	}


}

Texture::Texture(unsigned char* buffer, const int& width, const int& height, const int& bpp) :
	rendererID(0), width(width), height(height), bpp(bpp), VAO(0), VBO(0)
{
	glGenTextures(1, &rendererID);
	glBindTexture(GL_TEXTURE_2D, rendererID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	std::vector<float> positions = { 0,0,0,0,(float)width ,0 ,1.0f ,0,(float)width ,(float)height ,1.0f,1.0f,0,(float)height,0 ,1.0 };

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Texture::dispose() const
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteTextures(1, &rendererID);
}

void Texture::draw() const
{
	bind();
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	unbind();
}

void Texture::bind() const
{
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, rendererID);
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
				int pixelIndex = 4 * (y * width + x);
				int bitmapPixelIndex = 4 * ((y + bitmapHeight - height) * bitmapWidth + x + i * width);
				tempBuffer[pixelIndex] = localBuffer[bitmapPixelIndex];
				tempBuffer[pixelIndex + 1] = localBuffer[bitmapPixelIndex + 1];
				tempBuffer[pixelIndex + 2] = localBuffer[bitmapPixelIndex + 2];
				tempBuffer[pixelIndex + 3] = localBuffer[bitmapPixelIndex + 3];
			}
		}

		results.push_back(Texture(tempBuffer, width, height, bpp));

		delete[] tempBuffer;
	}

	std::cout << "[class Texture] " << path << " Load complete!\n";

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

const bool Texture::operator==(const Texture& texture)
{
	return rendererID == texture.rendererID;
}

