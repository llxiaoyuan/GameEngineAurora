#include<Aurora/Configuration.hpp>

Configuration::Configuration(const int& screenWidth, const int& screenHeight, const std::string& title, const DisplayMode& mode, const bool& useAudio, const int& multiSample, const size_t& frameTotal, const size_t& interval) :
	screenWidth(screenWidth), screenHeight(screenHeight), title(title), mode(mode), useAudio(useAudio), multiSample(multiSample), frameTotal(frameTotal), interval(interval)
{
}
