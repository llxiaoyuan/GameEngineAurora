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

	~BitmapTexture();

private:

	BitmapTexture(const unsigned char* const buffer, const int& width, const int& height, const int& bpp);

	friend class SpriteRenderer;

	friend class BitmapFont;

	//贴图宽
	int width;

	//贴图高
	int height;

	//文件源
	std::string filePath;

	int bpp;

	unsigned int VBO;

	unsigned int instanceVBO;

	unsigned int colorVBO;

	unsigned int VAO;

	unsigned int rendererID;

	//默认的最大矩阵数
	static constexpr int defaultMaxMatricesNum = 1200;

	glm::mat4* modelMatrices;

	glm::vec4* colors;

	int curMatricesNum;

	bool registered;

	//绑定贴图
	void bind() const;

	//执行实例化渲染
	void drawInstance() const;

	//解绑贴图
	void unbind() const;

	//更新模型和颜色数据
	void update() const;

	//增加模型,如有需要请先调用addColor
	void addModel(const glm::mat4& model);

	//增加颜色,如果需要先调用addColor再掉用addModel
	void addColor(const float& r = 1.f, const float& g = 1.f, const float& b = 1.f, const float& a = 1.f);

	//SpriteRenderer的draw方法调用此方法来记录已经在贴图池中的的贴图
	void checkIn();

	//SpriteRenderer的end方法调用此方法来删除在贴图池中的贴图
	void checkOut();

	//此方法返回是否已经在贴图池中
	const bool& isRegistered() const;

};

#endif // !_BITMAP_TEXTURE_HPP_
