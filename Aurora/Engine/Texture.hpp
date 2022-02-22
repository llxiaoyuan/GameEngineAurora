#pragma once

#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include<glad/glad.h>
#include<string>
#include<iostream>
#include<stb_image/stb_image.h>
#include<vector>

class Texture
{
public:

	Texture(const std::string& path);

	Texture(unsigned char* buffer, const int& width, const int& height, const int& bpp);

	void dispose() const;

	void draw() const;

	void bind() const;

	void unbind() const;

	static std::vector<Texture> loadSplit(const std::string& path,const int& width,const int& height,const int& count);

	const int& getWidth() const;

	const int& getHeight() const;

private:

	int width;

	int height;

	const std::string filePath;

	int bpp;

	unsigned int VBO;

	unsigned int VAO;

	unsigned int rendererID;

};


#endif // !_TEXTURE_BUFFER_HPP_
