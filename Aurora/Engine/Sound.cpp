#include"Sound.hpp"

Sound::Sound(const char* filePath, const bool& loop, irrklang::ISound* sound):
	filePath(filePath),loop(loop),sound(sound)
{
}

Sound::~Sound()
{
	sound->drop();
}

const char* Sound::getFilePath() const
{
	return filePath;
}

const bool& Sound::getLoop() const
{
	return loop;
}
