#pragma once

#ifndef _ANIMATION_HPP_
#define _ANIMATION_HPP_

#include<vector>

#include"Graphics.hpp"
#include"Texture.hpp"

//������
class Animation
{
public:

	Animation(const float& frameDuration);

	~Animation();

	//������ͼ
	void addTexture(const Texture& texture);

	//����stateTime���ش�ʱ����ͼ
	Texture& getTexture(const float& stateTime);

	//������ͼ
	std::vector<Texture> textures;

private:

	//��ͼÿһ֡��ʱ��
	const float frameDuration;
	
};

#endif // !_ANIMATION_HPP_
