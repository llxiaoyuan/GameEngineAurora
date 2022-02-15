#pragma once

#ifndef _ANIMATION_HPP_
#define _ANIMATION_HPP_

#include<vector>

#include"Graphics.hpp"
#include"Texture.hpp"

class Animation
{
public:

	Animation(const float& frameDuration);

	void addTexture(Texture texture);

	Texture& getTexture();

	std::vector<Texture> textures;

private:

	size_t curIndex;

	float curTime;

	const float frameDuration;

};

#endif // !_ANIMATION_HPP_
