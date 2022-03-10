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

	//从文件中读取贴图
	Texture(const std::string& path);

	//专门用于从图集读取贴图
	Texture(unsigned char* buffer, const int& width, const int& height, const int& bpp, const bool& isBitmapFontTexture);

	//释放资源
	void dispose() const;

	//从图集中读取贴图
	static std::vector<Texture> loadSplit(const std::string& path, const int& width, const int& height, const int& count);

	//返回贴图宽
	const int& getWidth() const;

	//返回贴图高
	const int& getHeight() const;

private:

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

	std::vector<glm::mat4> modelMatrices;

	std::vector<glm::vec4> colors;

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

	//更新颜色数据
	void updateColors() const;

	//增加模型,如有需要请先调用addColor
	void addModel(const glm::mat4& model);

	//增加颜色,如果需要先调用addColor再掉用addModel
	void addColor(const float& r = 1.f, const float& g = 1.f, const float& b = 1.f, const float& a = 1.f);

	//通过rendererID判断是否相等
	bool operator==(const Texture& texture) const;

	//默认的最大矩阵数 计算之后每个贴图占 1mb内存
	static constexpr int defaultMaxMatricesNum = 16384;

	//SpriteRenderer的draw方法调用此方法来记录已经在贴图池中的的贴图
	void checkIn();

	//SpriteRenderer的end方法调用此方法来删除在贴图池中的贴图
	void checkOut();

	//此方法返回是否已经在贴图池中
	const bool& isRegistered() const;

};


#endif // !_TEXTURE_BUFFER_HPP_
