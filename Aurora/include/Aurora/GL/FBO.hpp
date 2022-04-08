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

	void bindFBO() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	}

	void unbindFBO() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	unsigned int attachTexture(unsigned int id = 0) const
	{
		glActiveTexture(GL_TEXTURE0 + id);
		glBindTexture(GL_TEXTURE_2D, textureID);
		return id;
	}

	void dettachTexture() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	const int width;

	const int height;

	const float texelSizeX;

	const float texelSizeY;

	unsigned int fbo;

	unsigned int textureID;

private:

	friend class GL;

	FBO(const int& width, const int& height, const float& r, const float& g, const float& b, const float& a) :
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
		{
			std::cout << "[class RenderTexture] framebuffer is not complete!\n";
		}

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
		{
			std::cout << "[class RenderTexture] framebuffer is not complete!\n";
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void operator=(const FBO&) = delete;

};

#endif // !_FBO_HPP_