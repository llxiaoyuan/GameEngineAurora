#include "Configuration.hpp"

Configuration::Configuration(const int& screenWidth, const int& screenHeight, const std::string& title,const DisplayMode& mode,const bool& useAudio):
	screenWidth(screenWidth),screenHeight(screenHeight),title(title),mode(mode),useAudio(useAudio)
{
}
