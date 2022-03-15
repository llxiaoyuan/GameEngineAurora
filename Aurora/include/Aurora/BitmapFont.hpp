#pragma once

#ifndef _BITMAP_FONT_HPP_
#define _BITMAP_FONT_HPP_

#include<string>
#include<vector>
#include<fstream>
#include<map>

#include"BitmapTexture.hpp"
#include"SpriteRenderer.hpp"

//位图字体类
class BitmapFont
{
public:

	static BitmapFont* create(const std::string& bitmapPath, const std::string& configFilePath, const int& fontSize = -1);

	~BitmapFont();

	//字符信息
	struct Character
	{
		int index;
		int xoffset;
		int yoffset;
		int xadvance;
	};

	//通过字符获取字体信息
	const Character& getCharacter(const char& c);

	//获取字体大小
	const int& getFontSize() const;

	//设置字体大小
	void setFontSize(const int& fontSize);

	//获取缩放比例
	const float& getScale() const;

	void draw(SpriteRenderer* const renderer, const std::string& context, const float& x, const float& y, const float& r = 1.f, const float& g = 1.f, const float& b = 1.f, const float& a = 1.f);

	void draw(SpriteRenderer* const renderer, const char& context, const float& x, const float& y, const float& r = 1.f, const float& g = 1.f, const float& b = 1.f, const float& a = 1.f);

private:

	BitmapFont(const std::string& bitmapPath, const std::string& configFilePath, const int& fontSize = -1);

	//字体大小
	int fontSize;

	//原始字体大小
	int originFontSize;

	//缩放比例
	float scale;

	//字体贴图
	std::vector<BitmapTexture*> textures;

	std::map<char, Character> keyMap;

};

#endif // !_BITMAP_FONT_HPP_
