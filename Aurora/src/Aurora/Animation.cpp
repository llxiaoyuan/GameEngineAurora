#include<Aurora/Animation.hpp>

Animation::Animation(const float& frameDuration) :
	frameDuration(frameDuration)
{
	
}

Animation::~Animation()
{
	for (size_t i = 0; i < textures.size(); i++)
	{
		textures[i].dispose();
	}
}

void Animation::addTexture(const Texture& texture)
{
	textures.push_back(texture);
}

Texture& Animation::getTexture(const float& stateTime)
{
	return textures[(size_t)(stateTime / frameDuration) % textures.size()];
}