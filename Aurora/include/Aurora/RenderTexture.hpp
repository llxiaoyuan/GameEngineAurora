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

	//�ͷ���Դ
	void dispose() const;

	//������ͼ��
	const int& getWidth() const;

	//������ͼ��
	const int& getHeight() const;

	void updatePixelData() const;

	void setPixel(const int& x, const int& y, const int& r, const int& g, const int& b, const int& a);

	//�㷨����http://www.roguebasin.com/index.php?title=Bresenham%27s_Line_Algorithm
	void drawLine(int x1, int y1, const int& x2, const int& y2, const int& r, const int& g, const int& b, const int& a);

private:

	friend class SpriteRenderer;

	//��ͼ��
	int width;

	//��ͼ��
	int height;

	unsigned char* buffer;

	unsigned int VAO;

	unsigned int VBO;

	unsigned int instanceVBO;

	unsigned int rendererID;

	//Ĭ�ϵ��������� ����֮��ÿ����ͼռ 1mb�ڴ�
	static constexpr int defaultMaxMatricesNum = 16384;

	std::array<glm::mat4, defaultMaxMatricesNum> modelMatrices;

	int curIndex;

	bool registered;

	//����ͼ
	void bind() const;

	//ִ��ʵ������Ⱦ
	void drawInstance() const;

	//�����ͼ
	void unbind() const;

	//����ģ������
	void updateMatrices() const;

	//����ģ��
	void addModel(const glm::mat4& model);

	//SpriteRenderer��draw�������ô˷�������¼�Ѿ�����ͼ���еĵ���ͼ
	void checkIn();

	//SpriteRenderer��end�������ô˷�����ɾ������ͼ���е���ͼ
	void checkOut();

	//�˷��������Ƿ��Ѿ�����ͼ����
	const bool& isRegistered() const;

};


#endif // !_RENDERTEXTURE_HPP_
