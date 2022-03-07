#pragma once

#ifndef _BITMAP_FONT_HPP_
#define _BITMAP_FONT_HPP_

#include<string>
#include<vector>
#include<fstream>
#include<map>

#include"SpriteRenderer.hpp"

class BitmapFont
{
public:

	BitmapFont(const std::string& bitmapPath, const std::string& configFilePath, const int& fontSize = -1);

	~BitmapFont();

	const Texture& getTexture(const int& index) const;

	struct Character
	{
		int index;
		int xoffset;
		int yoffset;
		int xadvance;
	};

	const Character& getCharacter(const char& c);

	const int& getFontSize() const;

	void setFontSize(const int& fontSize);

	const float& getScale() const;

	void draw(SpriteRenderer& renderer, const std::string& context, const float& x, const float& y, const float& r = 1.f, const float& g = 1.f, const float& b = 1.f, const float& a = 1.f);

	void draw(SpriteRenderer& renderer, const char& context, const float& x, const float& y, const float& r = 1.f, const float& g = 1.f, const float& b = 1.f, const float& a = 1.f);

private:

	int fontSize;

	int originFontSize;

	float scale;

	std::vector<Texture> textures;

	std::map<char, Character> keyMap;

};

#endif // !_BITMAP_FONT_HPP_
