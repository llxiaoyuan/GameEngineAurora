#pragma once

#ifndef _SOUND_HPP_

#include<irrKlang/irrKlang.h>

class Sound
{
public:

	Sound(const char* filePath,const bool& loop,irrklang::ISound* sound);

	~Sound();

	const char* getFilePath() const;

	const bool& getLoop() const;

private:

	irrklang::ISound* sound;
	const char* filePath;
	bool loop;
};

#endif // !_SOUND_HPP_
