#pragma once

#ifndef _SPRITE_RENDERER_HPP_
#define _SPRITE_RENDERER_HPP_

#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<vector>

#include"Math.hpp"
#include"Graphics.hpp"
#include"Texture.hpp"
#include"Actor.hpp"
#include"Shader.hpp"


class SpriteRenderer
{
public:

	SpriteRenderer();

	~SpriteRenderer();

	void begin();

	void end();

	void draw(Texture& texture, const float& x, const float& y);

	void draw(Texture& texture, const float& x, const float& y, const float& originX, const float& originY);

	void draw(Texture& texture, const float& x, const float& y, const float& originX, const float& originY, const float& rotation);

	void texturePoolAdd(Texture& texture);

	void bitmapTexturePoolAdd(Texture& texture);

	Shader textRenderShader;

	Shader instanceRenderShader;

private:

	std::vector<Texture*> texturePool;

	std::vector<Texture*> bitmapTexturePool;

};

#endif // !_SPRITE_RENDERER_HPP
