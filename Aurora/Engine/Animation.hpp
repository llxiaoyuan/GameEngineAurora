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

	~Animation();

	void addTexture(const Texture& texture);

	Texture& getTexture(const float& stateTime);

	std::vector<Texture> textures;

private:

	const float frameDuration;

};

#endif // !_ANIMATION_HPP_
