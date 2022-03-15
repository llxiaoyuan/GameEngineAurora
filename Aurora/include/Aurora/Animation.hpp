#pragma once

#ifndef _ANIMATION_HPP_
#define _ANIMATION_HPP_

#include<vector>

#include"Graphics.hpp"
#include"Texture.hpp"

//动画类
class Animation
{
public:

	Animation() = delete;

	Animation(const Animation&) = delete;

	static Animation* create(const float& frameDuration);

	~Animation();

	//增加贴图
	void addTexture(Texture* const texture);

	//根据stateTime返回此时的贴图
	Texture* getTexture(const float& stateTime);

	//动画贴图
	std::vector<Texture*> textures;

private:

	Animation(const float& frameDuration);

	//贴图每一帧的时间
	const float frameDuration;
	
};

#endif // !_ANIMATION_HPP_
