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

	//ִ��ʵ������Ⱦ
	void drawInstance() const;

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
