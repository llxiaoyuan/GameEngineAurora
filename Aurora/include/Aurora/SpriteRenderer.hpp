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

//��ͼ��Ⱦ
class SpriteRenderer
{
public:

	SpriteRenderer();

	~SpriteRenderer();

	//�ڵ���draw����ǰ�ȵ�����
	void begin();

	//����һ��SpriteRenderer��������е����ּ���ͼ
	void end();

	void draw(Texture& texture, const float& x, const float& y);

	void draw(Texture& texture, const float& x, const float& y, const float& originX, const float& originY);

	void draw(Texture& texture, const float& x, const float& y, const float& originX, const float& originY, const float& rotation);

	void draw(RenderTexture& renderTexture, const float& x, const float& y);

	//����ͼ����������ͼ
	void texturePoolAdd(Texture& texture);

	//��������ͼ����������ͼ
	void bitmapTexturePoolAdd(Texture& texture);

	void renderTexturePoolAdd(RenderTexture& renderTexture);

	Shader textRenderShader;

	Shader instanceRenderShader;

private:

	//��ͼ��
	std::vector<Texture*> texturePool;

	//���ֵ���ͼ��
	std::vector<Texture*> bitmapTexturePool;

	std::vector<RenderTexture*> renderTexturePool;

};

#endif // !_SPRITE_RENDERER_HPP
