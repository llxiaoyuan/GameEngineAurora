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
#include"BitmapTexture.hpp"

//��ͼ��Ⱦ
class SpriteRenderer
{
public:

	static SpriteRenderer* create();

	SpriteRenderer(const SpriteRenderer&) = delete;

	~SpriteRenderer();

	//�ڵ���draw����ǰ�ȵ�����
	void begin();

	//����һ��SpriteRenderer��������е����ּ���ͼ
	void end();

	void draw(Texture* const texture, const float& x, const float& y);

	void draw(Texture* const texture, const float& x, const float& y, const float& originX, const float& originY);

	void draw(Texture* const texture, const float& x, const float& y, const float& originX, const float& originY, const float& rotation);

	void draw(RenderTexture* const renderTexture, const float& x, const float& y);

	//����ͼ����������ͼ
	void texturePoolAdd(Texture* const texture);

	//��������ͼ����������ͼ
	void bitmapTexturePoolAdd(BitmapTexture* const texture);

	void renderTexturePoolAdd(RenderTexture* const renderTexture);

	Shader textRenderShader;

	Shader instanceRenderShader;

private:

	SpriteRenderer();

	//��ͼ��
	std::vector<Texture*> texturePool;
	
	//���ֵ���ͼ��
	std::vector<BitmapTexture*> bitmapTexturePool;

	std::vector<RenderTexture*> renderTexturePool;

};

#endif // !_SPRITE_RENDERER_HPP
