#pragma once

#ifndef _RENDERTEXTURE_HPP_
#define _RENDERTEXTURE_HPP_

#include<iostream>

#include<glad/glad.h>
#include<glm/glm.hpp>

#include"GL/GL.hpp"

class RenderTexture
{
public:

	static RenderTexture* create(const int& width, const int& height, const float& r = 0, const float& g = 0, const float& b = 0, const float& a = 0);

	RenderTexture() = delete;

	RenderTexture(const RenderTexture&) = delete;

	void operator=(const RenderTexture&) = delete;

	~RenderTexture();

	void bind() const;

	void unbind() const;

private:

	friend class SpriteRenderer;

	int width;

	int height;

	FBO* const fbo;

	unsigned int VAO;

	unsigned int VBO;

	unsigned int positionBuffer;

	static constexpr int defaultMaxMatricesNum = 16384;

	glm::mat4* modelMatrices;

	int curMatricesNum;

	bool registered;

	RenderTexture(const int& width, const int& height, const float& r = 0, const float& g = 0, const float& b = 0, const float& a = 0);

	void drawInstance() const;

	void updateMatrices() const;

	void addModel(const glm::mat4& model);

	void checkIn();

	void checkOut();

	const bool& isRegistered() const;

};


#endif // !_RENDERTEXTURE_HPP_
