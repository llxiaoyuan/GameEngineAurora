#include<Aurora/Music.hpp>

irrklang::ISoundEngine* Music::soundEngine = nullptr;


void Music::play(const Sound& sound)
{
	soundEngine->play2D(sound.getFilePath(), sound.getLoop());
}

Sound Music::load(const char* filePath, const bool& loop)
{
	irrklang::ISound* sound = soundEngine->play2D(filePath, loop, true, true);
	return Sound(filePath, loop, sound);
}

void Music::ini()
{
	soundEngine = irrklang::createIrrKlangDevice();
}