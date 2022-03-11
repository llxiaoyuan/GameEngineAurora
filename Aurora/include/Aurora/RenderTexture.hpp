#pragma once

#ifndef _RENDERTEXTURE_HPP_
#define _RENDERTEXTURE_HPP_

#include<glad/glad.h>
#include<glm/glm.hpp>
#include<array>
#include<iostream>
#include<vector>
#include<stb_image/stb_image.h>

class RenderTexture
{
public:

public:

	RenderTexture(const int& width, const int& height, const int& r, const int& g, const int& b, const int& a);

	//释放资源
	void dispose() const;

	//返回贴图宽
	const int& getWidth() const;

	//返回贴图高
	const int& getHeight() const;

	void updatePixelData() const;

	void setPixel(const int& x, const int& y, const int& r, const int& g, const int& b, const int& a);

	//算法来自http://www.roguebasin.com/index.php?title=Bresenham%27s_Line_Algorithm
	void drawLine(int x1, int y1, const int& x2, const int& y2, const int& r, const int& g, const int& b, const int& a);

private:

	friend class SpriteRenderer;

	//贴图宽
	int width;

	//贴图高
	int height;

	unsigned char* buffer;

	unsigned int VAO;

	unsigned int VBO;

	unsigned int instanceVBO;

	unsigned int rendererID;

	//默认的最大矩阵数 计算之后每个贴图占 1mb内存
	static constexpr int defaultMaxMatricesNum = 16384;

	std::array<glm::mat4, defaultMaxMatricesNum> modelMatrices;

	int curIndex;

	bool registered;

	//绑定贴图
	void bind() const;

	//执行实例化渲染
	void drawInstance() const;

	//解绑贴图
	void unbind() const;

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
