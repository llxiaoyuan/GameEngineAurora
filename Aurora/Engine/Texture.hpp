#pragma once

#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include<glad/glad.h>
#include<string>
#include<iostream>
#include<stb_image/stb_image.h>
#include<vector>
#include<glm/glm.hpp>

class Texture
{
public:

	Texture();

	Texture(const std::string& path);

	Texture(unsigned char* buffer, const int& width, const int& height, const int& bpp, const bool& isBitmapFontTexture);

	void dispose() const;

	static std::vector<Texture> loadSplit(const std::string& path, const int& width, const int& height, const int& count);

	const int& getWidth() const;

	const int& getHeight() const;

	void bind() const;

	void unbind() const;

	void updateMatrices() const;

	void updateColors() const;

	//如有需要请先调用addColor
	void addModel(const glm::mat4& model);

	//如果需要先调用addColor再掉用addModel addModel会使curIndex自增1
	void addColor(const float& r = 1.f, const float& g = 1.f, const float& b = 1.f, const float& a = 1.f);

	const int& getInstanceNum() const;

	bool operator==(const Texture& texture) const;

	static const int defaultMaxMatricesNum;

	const unsigned int& getRenderID() const;

	void checkIn();

	void checkOut();

	const bool& isRegistered();

private:

	int width;

	int height;

	std::string filePath;

	int bpp;

	unsigned int VBO;

	unsigned int instanceVBO;

	unsigned int colorVBO;

	unsigned int VAO;

	unsigned int rendererID;


	std::vector<glm::mat4> modelMatrices;

	std::vector<glm::vec4> colors;

	int curIndex;

	bool registered;

};


#endif // !_TEXTURE_BUFFER_HPP_
