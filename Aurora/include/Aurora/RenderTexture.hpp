#pragma once

#ifndef _RENDERTEXTURE_HPP_
#define _RENDERTEXTURE_HPP_

#include<glad/glad.h>
#include<glm/glm.hpp>
#include<iostream>
#include<array>

class RenderTexture
{
public:

	RenderTexture(const int& width, const int& height, const float& r = 0, const float& g = 0, const float& b = 0, const float& a = 0);

	~RenderTexture();

	void bind() const;

	void unbind() const;

private:

	friend class SpriteRenderer;

	int width;

	int height;

	unsigned int FBO;

	unsigned int VAO;

	unsigned int VBO;

	unsigned int instanceVBO;

	unsigned int texColorBuffer;

	unsigned int rbo;

	static constexpr int defaultMaxMatricesNum = 16384;

	std::array<glm::mat4, defaultMaxMatricesNum> modelMatrices;

	int curMatricesNum;

	bool registered;

	//执行实例化渲染
	void drawInstance() const;

	//更新模型数据
	void updateMatrices() const;

	//增加模型
	void addModel(const glm::mat4& model);

	//SpriteRenderer的draw方法调用此方法来记录已经在贴图池中的的贴图
	void checkIn();

	//SpriteRenderer的end方法调用此方法来删除在贴图池中的贴图
	void checkOut();

	//此方法返回是否已经在贴图池中
	const bool& isRegistered() const;

};


#endif // !_RENDERTEXTURE_HPP_
