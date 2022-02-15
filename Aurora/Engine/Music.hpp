#pragma once

#ifndef _MUSIC_HPP_
#define _MUSIC_HPP_

#include<irrKlang/irrKlang.h>

#include"Aurora.hpp"

class Music
{
public:

	static void play(const char* filePath,const bool& loop);

private:

	static void ini();

	static irrklang::ISoundEngine* soundEngine;

	friend class Aurora;

};


#endif // !_MUSIC_HPP_