#pragma once

#ifndef _SPRITE_RENDERER_HPP_
#define _SPRITE_RENDERER_HPP_

#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<vector>

#include"Math.hpp"
#include"Graphics.hpp"
#include"BitmapFont.hpp"
#include"Actor.hpp"
#include"Shader.hpp"


class SpriteRenderer
{
public:

	SpriteRenderer();

	~SpriteRenderer();

	void begin();

	void end();

	void draw(Actor& actor);

	void draw(BitmapFont& bitmapFont, const std::string& context, const float& x, const float& y, const float& r = 1, const float& g = 1, const float& b = 1, const float& a = 1) const;

	void draw(BitmapFont& bitmapFont, const char& c, const float& x, const float& y, const float& r = 1, const float& g = 1, const float& b = 1, const float& a = 1) const;

	void draw(Texture& texture, const float& x, const float& y, const float& originX, const float& originY, const float& rotation=0) const;

	void draw(Texture& texture, const float& x, const float& y) const;

	std::vector<Texture*> drawTexture;

	Shader defaultShader;

};

#endif // !_SPRITE_RENDERER_HPP
