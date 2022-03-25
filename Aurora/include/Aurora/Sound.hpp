#pragma once

#ifndef _SOUND_HPP_
#define _SOUND_HPP_

#include<Fmod/fmod.hpp>

class Sound
{
public:

	static Sound* create(const char* filePath, const bool& loop = false);

	~Sound();

	const char* getFilePath() const;

	const bool& getLoop() const;

	void play();

private:

	Sound(const char* filePath, const bool& loop);

	friend class Aurora;

	static void ini();

	static void release();

	static FMOD::System* system;
	static FMOD::Channel* channel;

	const char* filePath;
	bool loop;

	FMOD::Sound* sound;
};

#endif // !_SOUND_HPP_
