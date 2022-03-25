#include<Aurora/Aurora.hpp>

#include"MyGame.hpp"

int main(int argc, const char* argv[])
{
	int resolutionX = 960;
	int resolutionY = 540;
	std::string title = u8"Aurora Test";
	Configuration::DisplayMode displayMode = Configuration::DisplayMode::Normal;
	bool useAudio = true;
	int multisampleLevel = 4;

	Configuration config(resolutionX, resolutionY, title, displayMode, useAudio, multisampleLevel);
	Aurora::get().iniEngine(config);
	Aurora::get().iniGame(new MyGame());
	return 0;
}