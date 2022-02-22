#include"Animation.hpp"

Animation::Animation(const float& frameDuration) :
	frameDuration(frameDuration)
{
	
}

void Animation::addTexture(Texture texture)
{
	textures.push_back(texture);
}

Texture& Animation::getTexture(const float& stateTime)
{
	return textures[(size_t)(stateTime / frameDuration) % textures.size()];
}