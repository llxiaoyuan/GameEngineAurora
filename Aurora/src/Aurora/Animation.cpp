#include<Aurora/Animation.hpp>

Animation::Animation(const float& frameDuration) :
	frameDuration(frameDuration)
{
	
}

Animation* Animation::create(const float& frameDuration)
{
	return new Animation(frameDuration);
}

Animation::~Animation()
{
	for (size_t i = 0; i < textures.size(); i++)
	{
		delete textures[i];
	}
}

void Animation::addTexture(Texture* const texture)
{
	textures.push_back(texture);
}

Texture* Animation::getTexture(const float& stateTime)
{
	return textures[(size_t)(stateTime / frameDuration) % textures.size()];
}