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

	//���ļ��ж�ȡ��ͼ
	Texture(const std::string& path);

	//ר�����ڴ�ͼ����ȡ��ͼ
	Texture(unsigned char* buffer, const int& width, const int& height, const int& bpp, const bool& isBitmapFontTexture);

	//�ͷ���Դ
	void dispose() const;

	//��ͼ���ж�ȡ��ͼ
	static std::vector<Texture> loadSplit(const std::string& path, const int& width, const int& height, const int& count);

	//������ͼ��
	const int& getWidth() const;

	//������ͼ��
	const int& getHeight() const;

private:

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

	std::vector<glm::mat4> modelMatrices;

	std::vector<glm::vec4> colors;

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

	//������ɫ����
	void updateColors() const;

	//����ģ��,������Ҫ���ȵ���addColor
	void addModel(const glm::mat4& model);

	//������ɫ,�����Ҫ�ȵ���addColor�ٵ���addModel
	void addColor(const float& r = 1.f, const float& g = 1.f, const float& b = 1.f, const float& a = 1.f);

	//ͨ��rendererID�ж��Ƿ����
	bool operator==(const Texture& texture) const;

	//Ĭ�ϵ��������� ����֮��ÿ����ͼռ 1mb�ڴ�
	static constexpr int defaultMaxMatricesNum = 16384;

	//SpriteRenderer��draw�������ô˷�������¼�Ѿ�����ͼ���еĵ���ͼ
	void checkIn();

	//SpriteRenderer��end�������ô˷�����ɾ������ͼ���е���ͼ
	void checkOut();

	//�˷��������Ƿ��Ѿ�����ͼ����
	const bool& isRegistered() const;

};


#endif // !_TEXTURE_BUFFER_HPP_
