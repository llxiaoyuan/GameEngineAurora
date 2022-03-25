#include<Aurora/Sound.hpp>

FMOD::System* Sound::system = nullptr;
FMOD::Channel* Sound::channel = nullptr;

Sound::Sound(const char* filePath, const bool& loop):
	filePath(filePath),loop(loop),sound(nullptr)
{
	system->createSound(filePath, FMOD_DEFAULT, 0, &sound);
	if (loop)
	{
		sound->setMode(FMOD_LOOP_NORMAL);
	}
	else
	{
		sound->setMode(FMOD_LOOP_OFF);
	}
}

Sound* Sound::create(const char* filePath, const bool& loop)
{
	return new Sound(filePath, loop);
}

Sound::~Sound()
{
	sound->release();
}

const char* Sound::getFilePath() const
{
	return filePath;
}

const bool& Sound::getLoop() const
{
	return loop;
}

void Sound::play()
{
	system->playSound(sound, 0, false, &channel);
	system->update();
}

void Sound::ini()
{
	FMOD::System_Create(&system);
	system->init(32, FMOD_INIT_NORMAL, nullptr);
}

void Sound::release()
{
	system->close();
	system->release();
}
