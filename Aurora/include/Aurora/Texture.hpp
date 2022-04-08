#pragma once

#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include<iostream>
#include<string>
#include<vector>

#include<glad/glad.h>
#include<stb_image/stb_image.h>
#include<glm/glm.hpp>

class Texture
{
public:

	Texture() = delete;

	Texture(const Texture&) = delete;

	void operator=(const Texture&) = delete;

	static Texture* create(const std::string& path);

	~Texture();

	static std::vector<Texture*> loadSplit(const std::string& path, const int& width, const int& height, const int& count);

	const int& getWidth() const;

	const int& getHeight() const;

private:

	friend class SpriteRenderer;

	int width;

	int height;

	const std::string filePath;

	int bpp;

	unsigned int VAO;

	unsigned int VBO;

	unsigned int positionBuffer;

	unsigned int textureID;
	
	//默认的最大矩阵数 计算之后每个贴图占 1mb内存
	static constexpr int defaultMaxMatricesNum = 16384;

	glm::mat4* modelMatrices;

	int curMatricesNum;

	bool registered;

	Texture(const std::string& path);

	Texture(const unsigned char* const buffer, const int& width, const int& height, const int& bpp);

	void bind() const;

	void drawInstance() const;

	void unbind() const;

	void updateMatrices() const;

	void addModel(const glm::mat4& model);

	void checkIn();

	void checkOut();

	const bool& isRegistered() const;

};

using TexturePtr = Texture*;


#endif // !_TEXTURE_BUFFER_HPP_
