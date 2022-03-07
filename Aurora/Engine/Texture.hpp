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

	Texture(unsigned char* buffer, const int& width, const int& height, const int& bpp,const bool& needInstanceRender);

	void dispose() const;

	static std::vector<Texture> loadSplit(const std::string& path,const int& width,const int& height,const int& count);

	const int& getWidth() const;

	const int& getHeight() const;

	void bind() const;

	void unbind() const;

	void updateMatrices() const;

	void addModel(const glm::mat4& model);

	const int& getInstanceNum() const;

	void resetInstanceNum();

	bool operator==(const Texture& texture) const;

	static const int maxMatricesNum;

	const unsigned int& getRenderID() const;

private:

	int width;

	int height;

	std::string filePath;

	int bpp;

	unsigned int VBO;

	unsigned int instanceVBO;

	unsigned int VAO;

	unsigned int rendererID;

	std::vector<glm::mat4> modelMatrices;

	int curIndex;

};


#endif // !_TEXTURE_BUFFER_HPP_
