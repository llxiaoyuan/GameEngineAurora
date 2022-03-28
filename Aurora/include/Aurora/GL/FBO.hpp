#pragma once

#ifndef _FBO_HPP_
#define _FBO_HPP_

#include<iostream>
#include<glad/glad.h>

class FBO
{
public:

	FBO() = delete;

	FBO(const FBO&) = delete;

	~FBO()
	{
		if (fbo)
		{
			glDeleteFramebuffers(1, &fbo);
		}
		if (textureID)
		{
			glDeleteTextures(1, &textureID);
		}
	}

	void bindFBO()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	}

	void unbindFBO()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	unsigned int attachTexture(unsigned int id = 0)
	{
		glActiveTexture(GL_TEXTURE0 + id);
		glBindTexture(GL_TEXTURE_2D, textureID);
		return id;
	}

	void dettachTexture()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	int width;

	int height;

	float texelSizeX;

	float texelSizeY;

	unsigned int fbo;

	unsigned int textureID;

private:

	friend class GL;

	FBO(const int& width, const int& height, const float& r = 0, const float& g = 0, const float& b = 0, const float& a = 0) :
		width(width), height(height), texelSizeX(1.f / width), texelSizeY(1.f / height), fbo(0), textureID(0)
	{
		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "[class RenderTexture] ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(r, g, b, a);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	FBO(const int& width, const int& height, const int& internalFormat, const unsigned int& format, const unsigned int& type, const int& param) :
		width(width), height(height), texelSizeX(1.f / width), texelSizeY(1.f / height), fbo(0), textureID(0)
	{
		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "[class RenderTexture] ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

};

#endif // !_FBO_HPP_