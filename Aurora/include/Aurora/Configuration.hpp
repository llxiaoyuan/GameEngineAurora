#pragma once

#ifndef _CONFIGURATION_HPP_
#define _CONFIGURATION_HPP_

#include<string>

//��Ϸ��ص�����
class Configuration
{
public:

	const enum class DisplayMode
	{
		Normal,
		Wallpaper,
		Record
	} mode;

	Configuration(const int& screenWidth, const int& screenHeight, const std::string& title, const DisplayMode& mode, const bool& useAudio, const int& multiSample = 0);

	const int screenWidth;

	const int screenHeight;

	const std::string title;

	const bool useAudio;

	const int multiSample;

};

#endif // !_CONFIGURATION_HPP_
