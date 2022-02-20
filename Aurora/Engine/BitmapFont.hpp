#pragma once

#ifndef _BITMAP_FONT_HPP_
#define _BITMAP_FONT_HPP_

#include<string>
#include<vector>
#include<fstream>
#include<map>

#include"Texture.hpp"

class BitmapFont
{
public:

	BitmapFont(const std::string& bitmapPath, const std::string& configFilePath, const int& fontSize = -1);

	~BitmapFont();

	Texture& getTexture(const int& index);

	struct Character
	{
		int index;
		int xoffset;
		int yoffset;
		int xadvance;
	};

	const Character& getCharacter(const char& c);

	const int& getFontSize();

	void setFontSize(const int& fontSize);

	const float& getScale();

private:

	int fontSize;

	int originFontSize;

	float scale;

	std::vector<Texture> texturebuffers;

	std::map<char, Character> keyMap;

};

#endif // !_BITMAP_FONT_HPP_
