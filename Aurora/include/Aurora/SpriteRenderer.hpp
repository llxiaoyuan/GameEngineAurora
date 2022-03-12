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
#include"RenderTexture.hpp"
#include"Actor.hpp"
#include"Shader.hpp"

//贴图渲染
class SpriteRenderer
{
public:

	SpriteRenderer();

	~SpriteRenderer();

	//在调用draw方法前先调用它
	void begin();

	//在这一刻SpriteRenderer会绘制所有的文字及贴图
	void end();

	void draw(Texture& texture, const float& x, const float& y);

	void draw(Texture& texture, const float& x, const float& y, const float& originX, const float& originY);

	void draw(Texture& texture, const float& x, const float& y, const float& originX, const float& originY, const float& rotation);

	void draw(RenderTexture& renderTexture, const float& x, const float& y);

	//向贴图池中增加贴图
	void texturePoolAdd(Texture& texture);

	//向文字贴图池中增加贴图
	void bitmapTexturePoolAdd(Texture& texture);

	void renderTexturePoolAdd(RenderTexture& renderTexture);

	Shader textRenderShader;

	Shader instanceRenderShader;

private:

	//贴图池
	std::vector<Texture*> texturePool;

	//文字的贴图池
	std::vector<Texture*> bitmapTexturePool;

	std::vector<RenderTexture*> renderTexturePool;

};

#endif // !_SPRITE_RENDERER_HPP
