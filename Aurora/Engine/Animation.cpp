#include"Animation.hpp"

Animation::Animation(const float& frameDuration) :
	frameDuration(frameDuration),curIndex(0),curTime(0)
{
	
}

void Animation::addTexture(Texture texture)
{
	textures.push_back(texture);
}

Texture& Animation::getTexture()
{
	curTime += Graphics::getDeltaTime();
	if (curTime >= frameDuration)
	{
		curTime = 0;
		curIndex++;
		if (curIndex == textures.size())
		{
			curIndex = 0;
		}
	}
	return textures[curIndex];
}