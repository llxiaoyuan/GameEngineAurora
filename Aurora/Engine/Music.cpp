#include"Music.hpp"

irrklang::ISoundEngine* Music::soundEngine;


void Music::play(const char* filePath,const bool& loop)
{
	soundEngine->play2D(filePath, loop);
}

void Music::ini()
{
	soundEngine = irrklang::createIrrKlangDevice();
}