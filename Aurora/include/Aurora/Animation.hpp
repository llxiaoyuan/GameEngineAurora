#pragma once

#ifndef _ANIMATION_HPP_
#define _ANIMATION_HPP_

#include<vector>

#include"Graphics.hpp"
#include"Texture.hpp"

class Animation
{
public:

	Animation() = delete;

	Animation(const Animation&) = delete;

	void operator=(const Animation&) = delete;

	static Animation* create(const float& frameDuration);

	~Animation();

	void addTexture(Texture* const texture);

	Texture* getTexture(const float& stateTime);

	std::vector<Texture*> textures;

private:

	Animation(const float& frameDuration);

	const float frameDuration;
	
};

#endif // !_ANIMATION_HPP_
