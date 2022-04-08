#pragma once

#ifndef _BITMAP_TEXTURE_HPP_
#define _BITMAP_TEXTURE_HPP_

#include<string>

#include<glad/glad.h>
#include<glm/glm.hpp>

class BitmapTexture
{
public:

	BitmapTexture() = delete;

	BitmapTexture(const BitmapTexture&) = delete;

	void operator=(const BitmapTexture&) = delete;

	~BitmapTexture();

private:

	BitmapTexture(const unsigned char* const buffer, const int& width, const int& height, const int& bpp);

	friend class SpriteRenderer;

	friend class BitmapFont;

	int width;

	int height;

	std::string filePath;

	int bpp;

	unsigned int VAO;

	unsigned int textureID;

	unsigned int VBO;

	unsigned int positionBuffer;

	unsigned int colorBuffer;

	static constexpr int defaultMaxMatricesNum = 1200;

	glm::mat4* modelMatrices;

	glm::vec4* colors;

	int curMatricesNum;

	bool registered;

	void bind() const;

	void drawInstance() const;

	void unbind() const;

	void update() const;

	void addModel(const glm::mat4& model);

	void addColor(const float& r = 1.f, const float& g = 1.f, const float& b = 1.f, const float& a = 1.f);

	void checkIn();

	void checkOut();

	const bool& isRegistered() const;

};

#endif // !_BITMAP_TEXTURE_HPP_
