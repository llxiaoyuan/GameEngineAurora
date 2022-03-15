#pragma once

#ifndef _BITMAP_FONT_HPP_
#define _BITMAP_FONT_HPP_

#include<string>
#include<vector>
#include<fstream>
#include<map>

#include"BitmapTexture.hpp"
#include"SpriteRenderer.hpp"

//λͼ������
class BitmapFont
{
public:

	static BitmapFont* create(const std::string& bitmapPath, const std::string& configFilePath, const int& fontSize = -1);

	~BitmapFont();

	//�ַ���Ϣ
	struct Character
	{
		int index;
		int xoffset;
		int yoffset;
		int xadvance;
	};

	//ͨ���ַ���ȡ������Ϣ
	const Character& getCharacter(const char& c);

	//��ȡ�����С
	const int& getFontSize() const;

	//���������С
	void setFontSize(const int& fontSize);

	//��ȡ���ű���
	const float& getScale() const;

	void draw(SpriteRenderer* const renderer, const std::string& context, const float& x, const float& y, const float& r = 1.f, const float& g = 1.f, const float& b = 1.f, const float& a = 1.f);

	void draw(SpriteRenderer* const renderer, const char& context, const float& x, const float& y, const float& r = 1.f, const float& g = 1.f, const float& b = 1.f, const float& a = 1.f);

private:

	BitmapFont(const std::string& bitmapPath, const std::string& configFilePath, const int& fontSize = -1);

	//�����С
	int fontSize;

	//ԭʼ�����С
	int originFontSize;

	//���ű���
	float scale;

	//������ͼ
	std::vector<BitmapTexture*> textures;

	std::map<char, Character> keyMap;

};

#endif // !_BITMAP_FONT_HPP_
