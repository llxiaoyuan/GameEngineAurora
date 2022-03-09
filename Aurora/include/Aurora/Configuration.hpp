#pragma once

#ifndef _CONFIGURATION_HPP_
#define _CONFIGURATION_HPP_

#include<string>

//游戏相关的配置
class Configuration
{
public:

	const enum class DisplayMode
	{
		Normal,
		Wallpaper
	} mode;

	Configuration(const int& screenWidth, const int& screenHeight, const std::string& title, const DisplayMode& mode,const bool& useAudio);

	const int screenWidth;

	const int screenHeight;

	const std::string title;

	const bool useAudio;

};

#endif // !_CONFIGURATION_HPP_
