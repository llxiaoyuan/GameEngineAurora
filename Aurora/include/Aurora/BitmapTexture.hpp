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

	//��ͼ��
	int width;

	//��ͼ��
	int height;

	//�ļ�Դ
	std::string filePath;

	int bpp;

	unsigned int VBO;

	unsigned int instanceVBO;

	unsigned int colorVBO;

	unsigned int VAO;

	unsigned int rendererID;

	//Ĭ�ϵ���������
	static constexpr int defaultMaxMatricesNum = 1200;

	glm::mat4* modelMatrices;

	glm::vec4* colors;

	int curMatricesNum;

	bool registered;

	//����ͼ
	void bind() const;

	//ִ��ʵ������Ⱦ
	void drawInstance() const;

	//�����ͼ
	void unbind() const;

	//����ģ�ͺ���ɫ����
	void update() const;

	//����ģ��,������Ҫ���ȵ���addColor
	void addModel(const glm::mat4& model);

	//������ɫ,�����Ҫ�ȵ���addColor�ٵ���addModel
	void addColor(const float& r = 1.f, const float& g = 1.f, const float& b = 1.f, const float& a = 1.f);

	//SpriteRenderer��draw�������ô˷�������¼�Ѿ�����ͼ���еĵ���ͼ
	void checkIn();

	//SpriteRenderer��end�������ô˷�����ɾ������ͼ���е���ͼ
	void checkOut();

	//�˷��������Ƿ��Ѿ�����ͼ����
	const bool& isRegistered() const;

};

#endif // !_BITMAP_TEXTURE_HPP_
